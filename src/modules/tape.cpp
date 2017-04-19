#include "tape.h"
#include "../audio/jack.h"
#include "../globals.h"
#include <plog/Log.h>
#include <sndfile.hh>
#include <thread>
#include <cmath>
#include <mutex>
#include <condition_variable>

#include "../ui/mainui.h"
#include "../ui/utils.h"

using namespace audio;
using namespace audio::jack;

const int BITRATE = SF_FORMAT_PCM_32;

void TapeModule::diskRoutine(TapeModule *self) {
  char *framebuf = (char*) malloc(rbSize);

  LOGI << "Position: " << self->sndfile.seek(0, SEEK_SET);

  while (1) {
    while (self->playing || self->recording) {
      if (self->playing) {
        auto space = jack_ringbuffer_write_space(self->playBuf);

        if (space >= SAMPLE_SIZE * nTracks) {
          uint nframes = space / (SAMPLE_SIZE * nTracks);
          uint size = SAMPLE_SIZE * nframes * nTracks;
          // Clear the framebuffer
          memset(framebuf, 0, size);

          auto read = self->sndfile.readf((AudioSample*) framebuf, nframes);

          if (read < nframes && !self->recording) {
            self->playing = false;
          }

          if (jack_ringbuffer_write(self->playBuf, framebuf, size) < size) {
            self->overruns++;
          }
        }
      }

      if (self->recording) {
        auto space = jack_ringbuffer_read_space(self->recBuf);

        if (space >= (SAMPLE_SIZE * nTracks)) {
          uint nframes = space / (SAMPLE_SIZE * nTracks);
          uint size = SAMPLE_SIZE * nframes * nTracks;

          memset(framebuf, 0, size);

          if (jack_ringbuffer_read(self->recBuf, framebuf, size) < size) {
            self->overruns++;
          };

          if (self->sndfile.writef((AudioSample*) framebuf, nframes) != nframes) {
            LOGF << "Cannot write sndfile:";
            LOGF << self->sndfile.strError();
            return;
          }
        }
      }
      LOGE_IF(self->overruns) << "Overruns: " << self->overruns;
    }
  }
}

/**
 * Mixes two signals.
 * @param A Signal A
 * @param B Signal B
 * @param ratio B:A, amount of B to mix into signal A.
 */
static inline AudioSample mix(AudioSample A, AudioSample B, float ratio = 0.5) {
  return A + (B - A) * ratio;
}

void TapeModule::process(uint nframes) {
  if (recording || playing) {
    uint bs = nTracks * SAMPLE_SIZE * nframes;
    if (bs > bufferSize) {
      LOGE << "Buffer too small: " << bufferSize << " of " << bs;
      exit(1);
    }
    if (playing) {
      if (jack_ringbuffer_read_space(playBuf) < bs) {
        // Wait for the disk thread to catch up
        // This is not a problem, since it only delays playback slightly
        // TODO: load even if there is no running playback
        return;
      }
      if (jack_ringbuffer_read(playBuf, (char *) buffer, bs) < bs) {
        // Shouldnt be possible at all because of the above check
        overruns++;
      };
    } else {
      memset(buffer, 0, bs);
    }
    if (recording) {
      for (uint f = 0; f < nframes; f++) {
        buffer[f * nTracks + track - 1] = GLOB.data.proc[f];
      }
      if (jack_ringbuffer_write(recBuf, (char *) buffer, bs) < bs) {
        overruns++;
      }
    }
  }

  mixOut(nframes);
}

void TapeModule::mixOut(jack_nframes_t nframes) {
  if (playing) { // mix the tracks
    // TODO: Configurable and all that
    AudioSample mixed;
    for (uint f = 0; f < nframes; f++) {
      mixed = buffer[f * nTracks];
      for (uint t = 1; t < nTracks ; t++) {
        mixed = mix(mixed, buffer[f * nTracks + t]);
      }
      GLOB.data.outL[f] = GLOB.data.outR[f] = mixed;
    }
  } else { // Just monitor the proc
    memcpy(GLOB.data.outL, GLOB.data.proc, nframes * SAMPLE_SIZE);
    memcpy(GLOB.data.outR, GLOB.data.proc, nframes * SAMPLE_SIZE);
  }
}

void TapeModule::exitThread(Module *arg) {
  auto *self = (TapeModule *) arg;
  self->recording = false;
  sf_close(self->sndfile.rawHandle());
}

void TapeModule::initThread(Module *arg) {
  LOGD << "Registered TapeModule";
  auto *self = (TapeModule *) arg;

  self->recBuf = jack_ringbuffer_create(
    self->rbSize);

  self->playBuf = jack_ringbuffer_create(
    self->rbSize);

  self->bufferSize = audio::SAMPLE_SIZE * GLOB.buffersize * nTracks;
  self->buffer = (audio::AudioSample *) malloc(self->bufferSize);
  LOGD << "Allocated " << self->bufferSize << " bytes for the buffer";
  /* Note from JACK sample capture_client.cpp:
   * When JACK is running realtime, jack_activate() will have
   * called mlockall() to lock our pages into memory.  But, we
   * still need to touch any newly allocated pages before
   * process() starts using them.  Otherwise, a page fault could
   * create a delay that would force JACK to shut us down.
   */
  memset(self->recBuf->buf, 0, self->recBuf->size);
  memset(self->playBuf->buf, 0, self->playBuf->size);
  memset(self->buffer, 0, self->bufferSize);

  int samplerate = GLOB.samplerate;
  int channels = self->nTracks;
  int format = SF_FORMAT_WAV | BITRATE;

  self->sndfile =
    SndfileHandle(GLOB.project->path, SFM_RDWR, format, channels, samplerate);

  if (self->sndfile.error()) {
    LOGE << "Cannot open sndfile '" <<
      GLOB.project->path.c_str() << "' for output:";
    LOGE << self->sndfile.strError() << ")";

    jack_client_close(GLOB.client);
    exit(1);
  }
  self->diskThread = std::thread(TapeModule::diskRoutine, self);

  MainUI::getInstance().currentScreen = self->tapeScreen;
}

TapeModule::TapeModule() : recording (false), playing (false), track (1),
                           tapeScreen (new TapeScreen(this))
{
  GLOB.events.postInit.add(this, TapeModule::initThread);
  GLOB.events.preExit.add(this, TapeModule::exitThread);
}

bool TapeScreen::keypress(ui::Key key) {
  switch (key) {
  case ui::K_REC:
    if (module->recording) {
      module->recording = false;
    } else {
      module->recording = true;
      module->playing = true;
    }
    return true;
  case ui::K_PLAY:
    if (module->playing) {
      module->playing = false;
      module->recording = false;
    } else {
      module->playing = true;
    }
    return true;
  case ui::K_TRACK_1:
    module->track = 1;
    return true;
  case ui::K_TRACK_2:
    module->track = 2;
    return true;
  case ui::K_TRACK_3:
    module->track = 3;
    return true;
  case ui::K_TRACK_4:
    module->track = 4;
    return true;
  }
}

auto COLOR_REEL_BACKGROUND = Cairo::SolidPattern::create_rgba(0, 0, 0, 1);
static inline void drawTapeReel(const ui::ContextPtr& cr, ui::PatternPtr col) {
  // Thanks svg2cairo, you are a savior!
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_source(COLOR_REEL_BACKGROUND); 
cr->begin_new_path();
cr->move_to(0, -51.5);
cr->curve_to(-28.441406, -51.5, -51.5, -28.441406, -51.5, 0);
cr->curve_to(-51.5, 28.441406, -28.441406, 51.5, 0, 51.5);
cr->curve_to(28.441406, 51.5, 51.5, 28.441406, 51.5, 0);
cr->curve_to(51.5, -28.441406, 28.441406, -51.5, 0, -51.5);
cr->close_path();
cr->move_to(0, -44.882812);
cr->curve_to(3.367188, -44.867188, 6.726562, -44.476562, 10.007812, -43.710938);
cr->curve_to(9.277344, -32.21875, 5.019531, -23.695312, 0, -23.679688);
cr->curve_to(-5.019531, -23.695312, -9.277344, -32.210938, -10.007812, -43.699219);
cr->curve_to(-6.726562, -44.46875, -3.371094, -44.863281, 0, -44.882812);
cr->close_path();
cr->move_to(0, -17.117188);
cr->curve_to(5.230469, -17.121094, 10.171875, -14.730469, 13.421875, -10.632812);
cr->curve_to(13.4375, -10.640625, 13.453125, -10.652344, 13.46875, -10.660156);
cr->curve_to(14.667969, -11.351562, 16.195312, -10.941406, 16.882812, -9.746094);
cr->curve_to(17.574219, -8.550781, 17.164062, -7.023438, 15.96875, -6.332031);
cr->curve_to(15.953125, -6.320312, 15.933594, -6.3125, 15.914062, -6.300781);
cr->curve_to(16.707031, -4.296875, 17.117188, -2.15625, 17.117188, 0);
cr->curve_to(17.113281, 8.484375, 10.890625, 15.683594, 2.5, 16.921875);
cr->curve_to(2.5, 16.949219, 2.5, 16.972656, 2.5, 17);
cr->curve_to(2.5, 18.378906, 1.378906, 19.5, 0, 19.5);
cr->curve_to(-1.378906, 19.5, -2.5, 18.378906, -2.5, 17);
cr->curve_to(-2.5, 16.972656, -2.496094, 16.941406, -2.496094, 16.914062);
cr->curve_to(-10.886719, 15.675781, -17.109375, 8.480469, -17.117188, 0);
cr->curve_to(-17.113281, -2.15625, -16.699219, -4.292969, -15.902344, -6.296875);
cr->curve_to(-15.925781, -6.308594, -15.949219, -6.320312, -15.96875, -6.332031);
cr->curve_to(-17.164062, -7.023438, -17.574219, -8.550781, -16.882812, -9.746094);
cr->curve_to(-16.195312, -10.941406, -14.667969, -11.351562, -13.46875, -10.664062);
cr->curve_to(-13.449219, -10.648438, -13.425781, -10.632812, -13.402344, -10.617188);
cr->curve_to(-10.164062, -14.71875, -5.226562, -17.113281, 0, -17.117188);
cr->close_path();
cr->move_to(0, -13.605469);
cr->curve_to(-7.511719, -13.605469, -13.605469, -7.511719, -13.601562, 0);
cr->curve_to(-13.605469, 7.511719, -7.511719, 13.605469, 0, 13.605469);
cr->curve_to(7.511719, 13.605469, 13.605469, 7.511719, 13.601562, 0);
cr->curve_to(13.605469, -7.511719, 7.511719, -13.605469, 0, -13.605469);
cr->close_path();
cr->move_to(0, -2.445312);
cr->curve_to(1.351562, -2.445312, 2.445312, -1.351562, 2.445312, 0);
cr->curve_to(2.445312, 1.351562, 1.351562, 2.445312, 0, 2.445312);
cr->curve_to(-1.351562, 2.445312, -2.445312, 1.351562, -2.445312, 0);
cr->curve_to(-2.445312, -1.351562, -1.351562, -2.445312, 0, -2.445312);
cr->close_path();
cr->move_to(27.332031, 8.925781);
cr->curve_to(31.660156, 8.867188, 37.273438, 10.410156, 42.894531, 13.207031);
cr->curve_to(40.890625, 19.660156, 37.453125, 25.578125, 32.84375, 30.515625);
cr->curve_to(23.257812, 24.140625, 18.007812, 16.195312, 20.507812, 11.839844);
cr->curve_to(21.527344, 10.074219, 23.761719, 9.0625, 26.910156, 8.9375);
cr->curve_to(27.046875, 8.929688, 27.1875, 8.925781, 27.332031, 8.925781);
cr->close_path();
cr->move_to(-28.046875, 8.925781);
cr->curve_to(-24.308594, 8.832031, -21.652344, 9.859375, -20.507812, 11.839844);
cr->curve_to(-18.003906, 16.191406, -23.257812, 24.148438, -32.851562, 30.527344);
cr->curve_to(-37.449219, 25.574219, -40.867188, 19.644531, -42.855469, 13.1875);
cr->curve_to(-37.566406, 10.5625, -32.269531, 9.035156, -28.046875, 8.925781);
cr->close_path();
cr->move_to(-28.046875, 8.925781);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->set_fill_rule(Cairo::FILL_RULE_WINDING);
cr->fill();
 /********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_line_width(1);
cr->set_miter_limit(4);
cr->set_line_cap(Cairo::LINE_CAP_ROUND);
cr->set_line_join(Cairo::LINE_JOIN_ROUND);
cr->set_source(col); 
cr->begin_new_path();
cr->move_to(0, -51.5);
cr->curve_to(-28.441406, -51.5, -51.5, -28.441406, -51.5, 0);
cr->curve_to(-51.5, 28.441406, -28.441406, 51.5, 0, 51.5);
cr->curve_to(28.441406, 51.5, 51.5, 28.441406, 51.5, 0);
cr->curve_to(51.5, -28.441406, 28.441406, -51.5, 0, -51.5);
cr->close_path();
cr->move_to(0, -44.882812);
cr->curve_to(3.367188, -44.867188, 6.726562, -44.476562, 10.007812, -43.710938);
cr->curve_to(9.277344, -32.21875, 5.019531, -23.695312, 0, -23.679688);
cr->curve_to(-5.019531, -23.695312, -9.277344, -32.210938, -10.007812, -43.699219);
cr->curve_to(-6.726562, -44.46875, -3.371094, -44.863281, 0, -44.882812);
cr->close_path();
cr->move_to(0, -17.117188);
cr->curve_to(5.230469, -17.121094, 10.171875, -14.730469, 13.421875, -10.632812);
cr->curve_to(13.4375, -10.640625, 13.453125, -10.652344, 13.46875, -10.660156);
cr->curve_to(14.667969, -11.351562, 16.195312, -10.941406, 16.882812, -9.746094);
cr->curve_to(17.574219, -8.550781, 17.164062, -7.023438, 15.96875, -6.332031);
cr->curve_to(15.953125, -6.320312, 15.933594, -6.3125, 15.914062, -6.300781);
cr->curve_to(16.707031, -4.296875, 17.117188, -2.15625, 17.117188, 0);
cr->curve_to(17.113281, 8.484375, 10.890625, 15.683594, 2.5, 16.921875);
cr->curve_to(2.5, 16.949219, 2.5, 16.972656, 2.5, 17);
cr->curve_to(2.5, 18.378906, 1.378906, 19.5, 0, 19.5);
cr->curve_to(-1.378906, 19.5, -2.5, 18.378906, -2.5, 17);
cr->curve_to(-2.5, 16.972656, -2.496094, 16.941406, -2.496094, 16.914062);
cr->curve_to(-10.886719, 15.675781, -17.109375, 8.480469, -17.117188, 0);
cr->curve_to(-17.113281, -2.15625, -16.699219, -4.292969, -15.902344, -6.296875);
cr->curve_to(-15.925781, -6.308594, -15.949219, -6.320312, -15.96875, -6.332031);
cr->curve_to(-17.164062, -7.023438, -17.574219, -8.550781, -16.882812, -9.746094);
cr->curve_to(-16.195312, -10.941406, -14.667969, -11.351562, -13.46875, -10.664062);
cr->curve_to(-13.449219, -10.648438, -13.425781, -10.632812, -13.402344, -10.617188);
cr->curve_to(-10.164062, -14.71875, -5.226562, -17.113281, 0, -17.117188);
cr->close_path();
cr->move_to(0, -13.605469);
cr->curve_to(-7.511719, -13.605469, -13.605469, -7.511719, -13.601562, 0);
cr->curve_to(-13.605469, 7.511719, -7.511719, 13.605469, 0, 13.605469);
cr->curve_to(7.511719, 13.605469, 13.605469, 7.511719, 13.601562, 0);
cr->curve_to(13.605469, -7.511719, 7.511719, -13.605469, 0, -13.605469);
cr->close_path();
cr->move_to(0, -2.445312);
cr->curve_to(1.351562, -2.445312, 2.445312, -1.351562, 2.445312, 0);
cr->curve_to(2.445312, 1.351562, 1.351562, 2.445312, 0, 2.445312);
cr->curve_to(-1.351562, 2.445312, -2.445312, 1.351562, -2.445312, 0);
cr->curve_to(-2.445312, -1.351562, -1.351562, -2.445312, 0, -2.445312);
cr->close_path();
cr->move_to(27.332031, 8.925781);
cr->curve_to(31.660156, 8.867188, 37.273438, 10.410156, 42.894531, 13.207031);
cr->curve_to(40.890625, 19.660156, 37.453125, 25.578125, 32.84375, 30.515625);
cr->curve_to(23.257812, 24.140625, 18.007812, 16.195312, 20.507812, 11.839844);
cr->curve_to(21.527344, 10.074219, 23.761719, 9.0625, 26.910156, 8.9375);
cr->curve_to(27.046875, 8.929688, 27.1875, 8.925781, 27.332031, 8.925781);
cr->close_path();
cr->move_to(-28.046875, 8.925781);
cr->curve_to(-24.308594, 8.832031, -21.652344, 9.859375, -20.507812, 11.839844);
cr->curve_to(-18.003906, 16.191406, -23.257812, 24.148438, -32.851562, 30.527344);
cr->curve_to(-37.449219, 25.574219, -40.867188, 19.644531, -42.855469, 13.1875);
cr->curve_to(-37.566406, 10.5625, -32.269531, 9.035156, -28.046875, 8.925781);
cr->close_path();
cr->move_to(-28.046875, 8.925781);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->stroke();
/********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_line_width(2.004047);
cr->set_miter_limit(4);
cr->set_line_cap(Cairo::LINE_CAP_BUTT);
cr->set_line_join(Cairo::LINE_JOIN_MITER);
cr->set_source(col); 
cr->begin_new_path();
cr->move_to(51.496094, 0);
cr->curve_to(51.496094, 28.441406, 28.441406, 51.496094, 0, 51.496094);
cr->curve_to(-28.441406, 51.496094, -51.496094, 28.441406, -51.496094, 0);
cr->curve_to(-51.496094, -28.441406, -28.441406, -51.496094, 0, -51.496094);
cr->curve_to(28.441406, -51.496094, 51.496094, -28.441406, 51.496094, 0);
cr->close_path();
cr->move_to(51.496094, 0);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->stroke();
/********************/
}

auto COLOR_TAPE = Cairo::SolidPattern::create_rgb(0.4, 0.4, 0.4);

static void drawStaticBackground(const ui::ContextPtr& cr, ui::PatternPtr recCol) {
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_line_width(2);
cr->set_miter_limit(4);
cr->set_line_cap(Cairo::LINE_CAP_ROUND);
cr->set_line_join(Cairo::LINE_JOIN_ROUND);
cr->set_source(COLOR_TAPE); 
cr->begin_new_path();
cr->move_to(265, 129);
cr->line_to(230, 182);
cr->curve_to(228.8125, 183.71875, 228.269531, 183.9375, 226, 184.5);
cr->line_to(189, 178.5);
cr->line_to(131, 178.5);
cr->line_to(94, 184.5);
cr->curve_to(90.882812, 184.15625, 90.234375, 183.242188, 89, 182.5);
cr->line_to(53.75, 142.476562);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->stroke_preserve();
/********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_source(COLOR_TAPE); 
cr->begin_new_path();
cr->move_to(237.5, 82.566406);
cr->curve_to(220.140625, 82.566406, 206.066406, 96.640625, 206.066406, 114);
cr->curve_to(206.066406, 131.359375, 220.140625, 145.433594, 237.5, 145.433594);
cr->curve_to(254.859375, 145.433594, 268.933594, 131.359375, 268.933594, 114);
cr->curve_to(268.933594, 96.640625, 254.859375, 82.566406, 237.5, 82.566406);
cr->close_path();
cr->move_to(237.5, 94.070312);
cr->curve_to(248.507812, 94.070312, 257.429688, 102.992188, 257.429688, 114);
cr->curve_to(257.429688, 125.007812, 248.507812, 133.929688, 237.5, 133.929688);
cr->curve_to(226.492188, 133.929688, 217.570312, 125.007812, 217.570312, 114);
cr->curve_to(217.570312, 102.992188, 226.492188, 94.070312, 237.5, 94.070312);
cr->close_path();
cr->move_to(82.5, 72.617188);
cr->curve_to(60.632812, 72.617188, 42.902344, 91.144531, 42.902344, 114);
cr->curve_to(42.902344, 136.855469, 60.632812, 155.382812, 82.5, 155.382812);
cr->curve_to(104.367188, 155.382812, 122.097656, 136.855469, 122.097656, 114);
cr->curve_to(122.097656, 91.144531, 104.367188, 72.617188, 82.5, 72.617188);
cr->close_path();
cr->move_to(82.5, 92.199219);
cr->curve_to(94.539062, 92.203125, 104.296875, 101.960938, 104.300781, 114);
cr->curve_to(104.296875, 126.039062, 94.539062, 135.796875, 82.5, 135.800781);
cr->curve_to(70.460938, 135.796875, 60.703125, 126.039062, 60.703125, 114);
cr->curve_to(60.703125, 101.960938, 70.460938, 92.203125, 82.5, 92.199219);
cr->close_path();
cr->move_to(82.5, 92.199219);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->set_fill_rule(Cairo::FILL_RULE_WINDING);
cr->fill_preserve();
 /********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_line_width(2);
cr->set_miter_limit(4);
cr->set_line_cap(Cairo::LINE_CAP_BUTT);
cr->set_line_join(Cairo::LINE_JOIN_MITER);
cr->set_source(COLOR_TAPE); 
cr->begin_new_path();
cr->move_to(237.5, 82.566406);
cr->curve_to(220.140625, 82.566406, 206.066406, 96.640625, 206.066406, 114);
cr->curve_to(206.066406, 131.359375, 220.140625, 145.433594, 237.5, 145.433594);
cr->curve_to(254.859375, 145.433594, 268.933594, 131.359375, 268.933594, 114);
cr->curve_to(268.933594, 96.640625, 254.859375, 82.566406, 237.5, 82.566406);
cr->close_path();
cr->move_to(237.5, 94.070312);
cr->curve_to(248.507812, 94.070312, 257.429688, 102.992188, 257.429688, 114);
cr->curve_to(257.429688, 125.007812, 248.507812, 133.929688, 237.5, 133.929688);
cr->curve_to(226.492188, 133.929688, 217.570312, 125.007812, 217.570312, 114);
cr->curve_to(217.570312, 102.992188, 226.492188, 94.070312, 237.5, 94.070312);
cr->close_path();
cr->move_to(82.5, 72.617188);
cr->curve_to(60.632812, 72.617188, 42.902344, 91.144531, 42.902344, 114);
cr->curve_to(42.902344, 136.855469, 60.632812, 155.382812, 82.5, 155.382812);
cr->curve_to(104.367188, 155.382812, 122.097656, 136.855469, 122.097656, 114);
cr->curve_to(122.097656, 91.144531, 104.367188, 72.617188, 82.5, 72.617188);
cr->close_path();
cr->move_to(82.5, 92.199219);
cr->curve_to(94.539062, 92.203125, 104.296875, 101.960938, 104.300781, 114);
cr->curve_to(104.296875, 126.039062, 94.539062, 135.796875, 82.5, 135.800781);
cr->curve_to(70.460938, 135.796875, 60.703125, 126.039062, 60.703125, 114);
cr->curve_to(60.703125, 101.960938, 70.460938, 92.203125, 82.5, 92.199219);
cr->close_path();
cr->move_to(82.5, 92.199219);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->stroke_preserve();
/********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_line_width(1);
cr->set_miter_limit(4);
cr->set_line_cap(Cairo::LINE_CAP_BUTT);
cr->set_line_join(Cairo::LINE_JOIN_MITER);
cr->set_source(recCol); 
cr->begin_new_path();
cr->move_to(98.046875, 179.5);
cr->curve_to(98.046875, 176.988281, 96.011719, 174.953125, 93.5, 174.953125);
cr->curve_to(90.988281, 174.953125, 88.953125, 176.988281, 88.953125, 179.5);
cr->curve_to(88.953125, 182.011719, 90.988281, 184.046875, 93.5, 184.046875);
cr->curve_to(96.011719, 184.046875, 98.046875, 182.011719, 98.046875, 179.5);
cr->close_path();
cr->move_to(98.046875, 179.5);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->stroke_preserve();
/********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_line_width(1);
cr->set_miter_limit(4);
cr->set_line_cap(Cairo::LINE_CAP_BUTT);
cr->set_line_join(Cairo::LINE_JOIN_MITER);
cr->set_source(recCol); 
cr->begin_new_path();
cr->move_to(230.046875, 179.5);
cr->curve_to(230.046875, 176.988281, 228.011719, 174.953125, 225.5, 174.953125);
cr->curve_to(222.988281, 174.953125, 220.953125, 176.988281, 220.953125, 179.5);
cr->curve_to(220.953125, 182.011719, 222.988281, 184.046875, 225.5, 184.046875);
cr->curve_to(228.011719, 184.046875, 230.046875, 182.011719, 230.046875, 179.5);
cr->close_path();
cr->move_to(230.046875, 179.5);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->stroke_preserve();
/********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_source(drawing::COLOR_BLACK); 
cr->begin_new_path();
cr->move_to(130.496094, 168.496094);
cr->line_to(134.496094, 188.503906);
cr->line_to(185.503906, 188.503906);
cr->line_to(189.503906, 168.496094);
cr->close_path();
cr->move_to(160, 189.253906);
cr->line_to(160, 220);
cr->close_path();
cr->move_to(160, 189.253906);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->set_fill_rule(Cairo::FILL_RULE_EVEN_ODD);
cr->fill_preserve();
 /********************/
cr->set_operator(Cairo::OPERATOR_OVER);
cr->set_line_width(1.703057);
cr->set_miter_limit(4);
cr->set_line_cap(Cairo::LINE_CAP_ROUND);
cr->set_line_join(Cairo::LINE_JOIN_ROUND);
cr->set_source(recCol); 
cr->begin_new_path();
cr->move_to(130.496094, 168.496094);
cr->line_to(134.496094, 188.503906);
cr->line_to(185.503906, 188.503906);
cr->line_to(189.503906, 168.496094);
cr->close_path();
cr->move_to(160, 189.253906);
cr->line_to(160, 220);
cr->close_path();
cr->move_to(160, 189.253906);
cr->set_tolerance(0.1);
cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
cr->stroke_preserve();
/********************/
}

void TapeScreen::draw(const ui::ContextPtr& cr) {
  using namespace drawing;

  static double rotation = 0;
  if (module->playing) {
    rotation += 2*M_PI/(6*60);
    if (rotation > 2*M_PI) rotation = 0;
  }

  auto recColor = (module->recording) ? COLOR_RED : COLOR_WHITE;

  cr->set_identity_matrix();
  drawStaticBackground(cr, recColor);

  cr->set_identity_matrix();
  cr->translate(82.5, 114);
  cr->rotate(-rotation);
  drawTapeReel(cr, recColor);

  cr->set_identity_matrix();
  cr->translate(WIDTH - 82.5, 114);
  cr->rotate(-rotation);
  drawTapeReel(cr, recColor);

  cr->set_identity_matrix();
  cr->set_source(COLOR_WHITE);
  cr->set_line_width(1);
  cr->rectangle(15, 15, 30, 30);
  cr->stroke();
  auto text1 = Pango::Layout::create(cr);
  text1->set_text(std::to_string(module->track));
  text1->set_font_description(FONT_BIG_NUM);
  int tw, th;
  text1->get_pixel_size(tw, th);

  cr->set_source(COLOR_WHITE);

  cr->move_to(15 + (30 - tw) / 2, 14 + (30 - th) / 2);
  text1->show_in_cairo_context(cr);

}

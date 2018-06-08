#if OTTO_AUDIO_ALSA

#include "alsa.hpp"

#include <string>
#include <vector>

#include <fmt/format.h>

/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API

/* All of the ALSA library API is defined
 * in this header */
#include <alsa/asoundlib.h>

#include "util/timer.hpp"

#include "core/audio/processor.hpp"
#include "core/globals.hpp"

#include "services/audio.hpp"
#include "services/engines.hpp"
#include "services/logger.hpp"

namespace otto::service::audio {

  static void debug_snd_params(snd_pcm_hw_params_t* params)
  {
    unsigned int val, val2;
    int dir;

    snd_pcm_hw_params_get_access(params, (snd_pcm_access_t*) &val);
    LOGI("access type = {}", snd_pcm_access_name((snd_pcm_access_t) val));

    snd_pcm_hw_params_get_format(params, (snd_pcm_format_t*) &val);
    LOGI("format = '{}' ({})", snd_pcm_format_name((snd_pcm_format_t) val),
         snd_pcm_format_description((snd_pcm_format_t) val));

    snd_pcm_hw_params_get_subformat(params, (snd_pcm_subformat_t*) &val);
    LOGI("subformat = '{}' ({})",
         snd_pcm_subformat_name((snd_pcm_subformat_t) val),
         snd_pcm_subformat_description((snd_pcm_subformat_t) val));

    snd_pcm_hw_params_get_channels(params, &val);
    LOGI("channels = {}", val);

    snd_pcm_hw_params_get_rate(params, &val, &dir);
    LOGI("rate = {} bps", val);

    snd_pcm_hw_params_get_period_time(params, &val, &dir);
    LOGI("period time = {} us", val);

    snd_pcm_uframes_t frames;
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
    LOGI("period size = {} frames", (int) frames);

    snd_pcm_hw_params_get_buffer_time(params, &val, &dir);
    LOGI("buffer time = {} us", val);

    snd_pcm_hw_params_get_buffer_size(params, (snd_pcm_uframes_t*) &val);
    LOGI("buffer size = {} frames", val);

    snd_pcm_hw_params_get_periods(params, &val, &dir);
    LOGI("periods per buffer = {} frames", val);

    snd_pcm_hw_params_get_rate_numden(params, &val, &val2);
    LOGI("exact rate = {}/{} bps", val, val2);

    val = snd_pcm_hw_params_get_sbits(params);
    LOGI("significant bits = {}", val);

    snd_pcm_hw_params_get_tick_time(params, &val, &dir);
    LOGI("tick time = {} us", val);

    val = snd_pcm_hw_params_is_batch(params);
    LOGI("is batch = {}", val);

    val = snd_pcm_hw_params_is_block_transfer(params);
    LOGI("is block transfer = {}", val);

    val = snd_pcm_hw_params_is_double(params);
    LOGI("is double = {}", val);

    val = snd_pcm_hw_params_is_half_duplex(params);
    LOGI("is half duplex = {}", val);

    val = snd_pcm_hw_params_is_joint_duplex(params);
    LOGI("is joint duplex = {}", val);

    val = snd_pcm_hw_params_can_overrange(params);
    LOGI("can overrange = {}", val);

    val = snd_pcm_hw_params_can_mmap_sample_resolution(params);
    LOGI("can mmap = {}", val);

    val = snd_pcm_hw_params_can_pause(params);
    LOGI("can pause = {}", val);

    val = snd_pcm_hw_params_can_resume(params);
    LOGI("can resume = {}", val);

    val = snd_pcm_hw_params_can_sync_start(params);
    LOGI("can sync start = {}", val);
  }

  AlsaAudioDriver& AlsaAudioDriver::get() noexcept
  {
    static AlsaAudioDriver instance{};
    return instance;
  }

  void AlsaAudioDriver::init()
  {
    int rc;
    snd_pcm_hw_params_t* params;

    /* Open PCM device for playback. */
    rc = snd_pcm_open(&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    LOGF_IF(rc < 0, "Unable to open PCM device: {}", snd_strerror(rc));

    /* Allocate a hardware parameters object. */
    rc = snd_pcm_hw_params_malloc(&params);
    LOGF_IF(rc < 0, "Unable to allocate hardware param struct: {}",
            snd_strerror(rc));

    /* Fill it in with default values. */
    rc = snd_pcm_hw_params_any(playback_handle, params);
    LOGF_IF(rc < 0, "Unable to initialize hardware param struct: {}",
            snd_strerror(rc));

    /* Set the desired hardware parameters. */

    /* Interleaved mode */
    rc = snd_pcm_hw_params_set_access(playback_handle, params,
                                      SND_PCM_ACCESS_RW_INTERLEAVED);
    LOGE_IF(rc < 0, "Error setting access: {}", snd_strerror(rc));

    /* Signed 16-bit little-endian format */
    rc = snd_pcm_hw_params_set_format(playback_handle, params,
                                      SND_PCM_FORMAT_FLOAT);
    LOGE_IF(rc < 0, "Error setting format: {}", snd_strerror(rc));

    /* Two channels (stereo) */
    rc = snd_pcm_hw_params_set_channels(playback_handle, params, 2);
    LOGE_IF(rc < 0, "Error setting channelse: {}", snd_strerror(rc));

    /* 44100 bits/second sampling rate (CD quality) */
    unsigned rate = 44100;
    int dir = 0;
    rc = snd_pcm_hw_params_set_rate_near(playback_handle, params, &rate, &dir);
    LOGE_IF(rc < 0, "Error setting sample rate: {}", snd_strerror(rc));

    // Set periods
    // unsigned periods = 4;
    // rc = snd_pcm_hw_params_set_periods(playback_handle, params, periods, 0);
    // LOGE_IF(rc < 0, "Error setting periods: {}", snd_strerror(rc));

    // snd_pcm_uframes_t sample_size = 4;
    // snd_pcm_uframes_t periodsize = sample_size * 2;
    // snd_pcm_uframes_t buffersize = 1024;
    // rc = snd_pcm_hw_params_set_buffer_size_near(playback_handle, params,
    // &buffersize); LOGE_IF(rc < 0, "Error setting buffer size: {}",
    // snd_strerror(rc));

    /* Display information about the PCM interface */

    LOGI("PCM playback_handle name = '{}'\n", snd_pcm_name(playback_handle));

    LOGI("PCM state = {}\n",
         snd_pcm_state_name(snd_pcm_state(playback_handle)));

    debug_snd_params(params);

    if (snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_DUPLEX, 0) < 0) {
        fprintf(stderr, "Error opening ALSA sequencer.\n");
        exit(1);
    }
    snd_seq_set_client_name(seq_handle, "OTTO");
    if (snd_seq_create_simple_port(seq_handle, "OTTO",
        SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
        SND_SEQ_PORT_TYPE_APPLICATION) < 0) {
        fprintf(stderr, "Error creating sequencer port.\n");
        exit(1);
    }

    LOGI("Opened sequencer");

    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(playback_handle, params);
    LOGF_IF(rc < 0, "Unable to set HW params: {}", snd_strerror(rc));

    audio_thread = std::thread([this] { main_loop(); });
  }

  void AlsaAudioDriver::shutdown()
  {
    snd_pcm_close(playback_handle);
    LOG_F(INFO, "Closing Alsa client");
  }

  int AlsaAudioDriver::process_callback(int nframes)
  {
    return nframes;
    auto running = audio::running() && global::running();
    if (!running) {
      return nframes;
    }

    TIME_SCOPE("AlsaAudio::Process");

    // gatherMidiInput(nframes);

    auto out_data = engines::process({{in_data.data(), nframes}, {}, nframes});

    audio::process_audio_output(out_data);

    LOGW_IF(out_data.nframes != nframes, "Frames went missing!");

    return snd_pcm_writei(playback_handle, out_data.audio.data(),
                          out_data.nframes);
  }

  void AlsaAudioDriver::main_loop()
  {
    int nfds = 0, l1 = 0;
    struct pollfd* pfds;
    const int BUFSIZE = 512;

    nfds = snd_pcm_poll_descriptors_count(playback_handle);
    pfds = (struct pollfd*) alloca(sizeof(struct pollfd) * nfds);
    snd_pcm_poll_descriptors(playback_handle, pfds, nfds);
    while (global::running()) {
      if (poll(pfds, nfds, 1000) > 0) {
        // for (l1 = 0; l1 < seq_nfds; l1++) {
        //   if (pfds[l1].revents > 0) midi_callback();
        // }
        for (l1 = 0; l1 < nfds; l1++) {
          if (pfds[l1].revents > 0) {
            if (process_callback(BUFSIZE) < BUFSIZE) {
              fprintf(stderr, "xrun !\n");
              snd_pcm_prepare(playback_handle);
            }
          }
        }
      }
    }
    snd_pcm_close(playback_handle);
    snd_seq_close(seq_handle);
  }
} // namespace otto::service::audio

#endif // OTTO_AUDIO_ALSA

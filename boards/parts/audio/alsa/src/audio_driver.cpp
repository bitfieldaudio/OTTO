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

  static int buffer_size = 512;
  static unsigned periods = 4;

  static void debug_snd_params(snd_pcm_hw_params_t* params)
  {

    {
      snd_pcm_access_t val;
      snd_pcm_hw_params_get_access(params, &val);
      LOGI("access type = {}", snd_pcm_access_name(val));
    }

    {
      snd_pcm_format_t val;
      snd_pcm_hw_params_get_format(params, &val);
      LOGI("format = '{}' ({})", snd_pcm_format_name(val),
           snd_pcm_format_description((snd_pcm_format_t) val));
    }

    {
      snd_pcm_subformat_t val;
      snd_pcm_hw_params_get_subformat(params, &val);
      LOGI("subformat = '{}' ({})",
           snd_pcm_subformat_name(val),
           snd_pcm_subformat_description(val));
    }

    unsigned int val;
    int dir;

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

    snd_pcm_hw_params_get_buffer_size(params, &frames);
    LOGI("buffer size = {} frames", val);

    snd_pcm_hw_params_get_periods(params, &val, &dir);
    LOGI("periods per buffer = {} frames", val);

    {
      unsigned int val2;
      snd_pcm_hw_params_get_rate_numden(params, &val, &val2);
      LOGI("exact rate = {}/{} bps", val, val2);
    }

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

  static void setup_alsa_device(snd_pcm_t* handle, int channels)
  {
    int rc;
    snd_pcm_hw_params_t* params;

    /* Allocate a hardware parameters object. */
    rc = snd_pcm_hw_params_malloc(&params);
    LOGF_IF(rc < 0, "Unable to allocate hardware param struct: {}",
            snd_strerror(rc));

    /* Fill it in with default values. */
    rc = snd_pcm_hw_params_any(handle, params);
    LOGF_IF(rc < 0, "Unable to initialize hardware param struct: {}",
            snd_strerror(rc));

    /* Set the desired hardware parameters. */

    /* Interleaved mode */
    rc = snd_pcm_hw_params_set_access(handle, params,
                                      SND_PCM_ACCESS_RW_INTERLEAVED);
    LOGE_IF(rc < 0, "Error setting access: {}", snd_strerror(rc));

    /* Signed 16-bit little-endian format */
    rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_FLOAT);
    LOGE_IF(rc < 0, "Error setting format: {}", snd_strerror(rc));

    /* Two channels (stereo) */
    rc = snd_pcm_hw_params_set_channels(handle, params, channels);
    LOGE_IF(rc < 0, "Error setting channelse: {}", snd_strerror(rc));

    unsigned rate = AudioDriver::get().samplerate;
    int dir = 0;
    rc = snd_pcm_hw_params_set_rate_near(handle, params, &rate, &dir);
    LOGE_IF(rc < 0, "Error setting sample rate: {}", snd_strerror(rc));
    AudioDriver::get().samplerate = rate;

    // Set periods
    rc = snd_pcm_hw_params_set_periods_near(handle, params, &periods, 0);
    LOGE_IF(rc < 0, "Error setting periods: {}", snd_strerror(rc));

    snd_pcm_uframes_t frame_size = channels * sizeof(float);
    snd_pcm_uframes_t frames = buffer_size * periods / frame_size;
    rc = snd_pcm_hw_params_set_buffer_size_near(handle, params, &frames);
    LOGE_IF(rc < 0, "Error setting buffer size: {}", snd_strerror(rc));

    if (frames != buffer_size * periods / frame_size) {
      buffer_size = frames * frame_size / periods;
    }

    /* Display information about the PCM interface */

    LOGI("PCM handle name = '{}'\n", snd_pcm_name(handle));

    LOGI("PCM state = {}\n", snd_pcm_state_name(snd_pcm_state(handle)));

    debug_snd_params(params);

    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    LOGF_IF(rc < 0, "Unable to set HW params: {}", snd_strerror(rc));
  }

  AlsaAudioDriver& AlsaAudioDriver::get() noexcept
  {
    static AlsaAudioDriver instance{};
    return instance;
  }

  void AlsaAudioDriver::init()
  {
    int rc;

    rc = snd_pcm_open(&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    LOGF_IF(rc < 0, "Unable to open PCM playback device: {}", snd_strerror(rc));
    rc = snd_pcm_open(&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    LOGF_IF(rc < 0, "Unable to open PCM playback device: {}", snd_strerror(rc));

    setup_alsa_device(playback_handle, 2);
    setup_alsa_device(capture_handle, 1);

    rc = snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_DUPLEX, 0);
    LOGF_IF(rc < 0, "Unable to open sequencer device: {}", snd_strerror(rc));

    snd_seq_set_client_name(seq_handle, "OTTO");
    rc = snd_seq_create_simple_port(
      seq_handle, "OTTO", SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
      SND_SEQ_PORT_TYPE_APPLICATION);
    LOGF_IF(rc < 0, "Error creating sequencer port: {}", snd_strerror(rc));

    LOGI("Opened sequencer");

    audio_thread = std::thread([this] { main_loop(); });

    events::buffersize_change().fire(buffer_size);
    events::samplerate_change().fire(samplerate);
  }

  void AlsaAudioDriver::shutdown()
  {
    snd_pcm_close(playback_handle);
    LOG_F(INFO, "Closing Alsa client");
  }

  int AlsaAudioDriver::process_callback(int nframes)
  {
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
    int nframes, inframes, outframes, frame_size;
    int channels = 2;
    frame_size = channels * sizeof(float);
    nframes = buffer_size / frame_size;

    bool restarting = true;

    while (global::running()) {
      if (restarting) {
        restarting = false;
        /* drop any output we might got and stop */
        snd_pcm_drop(capture_handle);
        snd_pcm_drop(playback_handle);
        /* prepare for use */
        snd_pcm_prepare(capture_handle);
        snd_pcm_prepare(playback_handle);

        /* fill the whole output buffer */
        for (int i = 0; i < periods; i += 1)
          snd_pcm_writei(playback_handle, in_data.data(), nframes);
      }

      while ((inframes =
                snd_pcm_readi(capture_handle, in_data.data(), nframes)) < 0) {
        if (inframes == -EAGAIN) continue;
        LOGE("Input Overrun");
        //restarting = 1;
        snd_pcm_prepare(capture_handle);
      }

      LOGE_IF(inframes != nframes,
              "Short read from capture device: {}, expecting {}", inframes,
              nframes);

      auto out_data =
        engines::process({{in_data.data(), nframes}, {}, nframes});

      audio::process_audio_output(out_data);

      LOGW_IF(out_data.nframes != nframes, "Frames went missing!");

      while ((outframes = snd_pcm_writei(playback_handle, out_data.audio.data(),
                                         out_data.nframes)) < 0) {
        if (outframes == -EAGAIN) continue;
        LOGE("Output buffer underrun");
        //restarting = 1;
        snd_pcm_prepare(playback_handle);
      }

      LOGE_IF(outframes != nframes,
              "Short write to capture device: {}, expecting {}", outframes,
              nframes);
    }
  }
} // namespace otto::service::audio

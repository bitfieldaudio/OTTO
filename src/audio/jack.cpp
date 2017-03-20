#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cerrno>
#include <csignal>

#include <sndfile.hh>
#include <pthread.h>
#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <plog/Log.h>

namespace audio {
  namespace jack {

    struct Project {
      std::string name;
      std::string path;
    };

    typedef struct ThreadInfo {
      jack_client_t *client;
      Project *project;
      struct Ports {
        int32_t count = 4;
        jack_port_t *outL;
        jack_port_t *outR;
        jack_port_t *out[2] = {
          outL,
          outR
        };
        jack_port_t *in[4];
      } ports;
      jack_nframes_t rbSize = 16384;
      volatile int canProcess;
    } jack_thread_info_t;

    const char *CLIENT_NAME = "tapedeck";
    const size_t SAMPLE_SIZE = sizeof(jack_default_audio_sample_t);

    jack_client_t *client;
    jack_ringbuffer_t *ringBuf;

    void shutdown(void *arg) {
      LOGI << "JACK shut down, exiting";
      exit(1);
    }

    int process(jack_nframes_t nframes, void *arg) {
      auto *jackInfo = (jack_thread_info_t *) arg;
    }

    void setupPorts(jack_thread_info_t *info) {
      ringBuf = jack_ringbuffer_create(info->ports.count * SAMPLE_SIZE * info->rbSize);

      memset(ringBuf->buf, 0, ringBuf->size);
    }

    int init (int argc, char *argv[]) {
      jack_thread_info_t jack_info;
      memset(&jack_info, 0, sizeof(jack_info));

      if ((client = jack_client_open(CLIENT_NAME, JackNullOption, NULL)) == 0) {
        LOGF << "JACK server not running";
        exit(1);
      }

      jack_info.client = client;
      jack_info.canProcess = 0;

      jack_set_process_callback(client, process, &jack_info);

      LOGE_IF(jack_activate(client)) << "Cannot activate JACK client";

      setupPorts(&jack_info);

      jack_client_close(client);

      exit(0);
    }
  }
}

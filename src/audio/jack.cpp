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

    struct ThreadInfo {
      jack_client_t *client;
      Project *project;
      struct Ports {
        const static int32_t count = 4;
        jack_port_t *outL;
        jack_port_t *outR;
        jack_port_t *out[2] = {outL, outR};
        jack_port_t *in[4];
      } ports;
      jack_nframes_t rbSize = 16384;
      volatile int canProcess;
    };

    const char *CLIENT_NAME = "tapedeck";
    const size_t SAMPLE_SIZE = sizeof(jack_default_audio_sample_t);

    jack_client_t *client;
    jack_ringbuffer_t *ringBuf;

    void shutdown(void *arg) {
      LOGI << "JACK shut down, exiting";
      exit(1);
    }

    int process(jack_nframes_t nframes, void *arg) {
      auto *jackInfo = (ThreadInfo *) arg;
    }

    void setupPorts(ThreadInfo *info) {
      size_t in_size = info->ports.count * sizeof(jack_default_audio_sample_t*);
      auto in = (jack_default_audio_sample_t **) malloc(in_size);

      ringBuf = jack_ringbuffer_create(
        info->ports.count * SAMPLE_SIZE * info->rbSize);

      /* Note from JACK sample capture_client.cpp:
       * When JACK is running realtime, jack_activate() will have
       * called mlockall() to lock our pages into memory.  But, we
       * still need to touch any newly allocated pages before
       * process() starts using them.  Otherwise, a page fault could
       * create a delay that would force JACK to shut us down.
       * TODO: Understand the above words
       */
      memset(ringBuf->buf, 0, ringBuf->size);
      memset(in, 0, in_size);

      // Register input ports
      for (int i = 0; i < info->ports.count; i++) {
        //TODO: replace std::string here
        std::string name = "input";
        name += std::to_string(i + 1);

        info->ports.in[i] = jack_port_register(
          info->client,
          name.c_str(),
          JACK_DEFAULT_AUDIO_TYPE,
          JackPortIsInput,
          0);
      }

      // function to register outputs
      auto registerOutput = [&](const char *name) {
        return jack_port_register(
          info->client,
          name,
          JACK_DEFAULT_AUDIO_TYPE,
          JackPortIsOutput,
          0);
      };
      // register output ports
      info->ports.outL = registerOutput("OutLeft");
      info->ports.outR = registerOutput("OutRight");

      // Find physical capture ports
      auto findPorts = [&](auto criteria)-> const char ** {
        const char **ports = jack_get_ports(
          info->client,
          NULL,
          NULL,
          criteria);
        if (ports == NULL) {
          LOGF << "No ports found matching " << std::to_string(criteria);
          jack_client_close(info->client);
          exit(1);
        }
        return ports;
      };

      // Helper function for connections
      auto connectPort = [&](jack_port_t *src, const char *dest_name) {
        if (jack_connect(info->client, dest_name, jack_port_name(src))) {
          LOGF << "Cannot connect port '" << jack_port_name(src)
          << "' to '" << dest_name << "'";
        }
      };

      const char **inputs  = findPorts(JackPortIsPhysical | JackPortIsInput);
      const char **outputs = findPorts(JackPortIsPhysical | JackPortIsOutput);

      unsigned int ninputs = 0;
      for (; inputs[ninputs] != NULL; ninputs++);
      unsigned int noutputs = 0;
      for (; outputs[noutputs] != NULL; noutputs++);

      for (int i = 0; i < info->ports.count; i++) {
        connectPort(info->ports.in[i], inputs[i % ninputs]);
      }

      connectPort(info->ports.outL, outputs[0 % noutputs]);
      connectPort(info->ports.outR, outputs[1 % noutputs]);

      info->canProcess = 1;
    }

    int init (int argc, char *argv[]) {
      ThreadInfo jack_info;
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

      sleep(10);

      jack_client_close(client);

      exit(0);
    }
  }
}

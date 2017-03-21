#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <cerrno>
#include <csignal>

#include <sndfile.hh>
#include <pthread.h>
#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <plog/Log.h>

namespace audio {

  typedef jack_default_audio_sample_t AudioSample;
  const size_t SAMPLE_SIZE = sizeof(AudioSample);

  namespace disk {
  }

  namespace jack {

    struct Project {
      std::string name;
      std::string path;
    };

    struct ThreadInfo {
      jack_client_t *client;
      jack_status_t status;
      Project *project;
      const static uint nout = 2;
      const static uint nin = 4;
      struct Ports {
        union { // In theory this allows to ways to access the outputs.
          struct {
            jack_port_t *outL;
            jack_port_t *outR;
          };
          jack_port_t *out[nout];
        };
        jack_port_t *in[nin];
      } ports;

      jack_nframes_t rbSize = 16384;

      struct Data {
        union { // Theres probably a better way to do it though
          struct {
            AudioSample *outL;
            AudioSample *outR;
          };
          AudioSample *out[2];
        };
      } data;

      volatile bool doProcess;
    };

    const char *CLIENT_NAME = "tapedeck";

    jack_client_t *client;
    jack_ringbuffer_t *ringBuf;

    void shutdown(void *arg) {
      LOGI << "JACK shut down, exiting";
      exit(1);
    }

    int process(jack_nframes_t nframes, void *arg) {
      auto *info = (ThreadInfo *) arg;

      if (!info->doProcess) return 0;

      for (uint i = 0; i < info->nout; i++)
        info->data.out[i] = (AudioSample *) jack_port_get_buffer(
          info->ports.out[i], nframes);

      // Play silence for now
      for (auto data: info->data.out)
        memset(data, 0, SAMPLE_SIZE);

      return 0;
    }

    void setupPorts(ThreadInfo *info) {
      size_t in_size = info->nin * sizeof(AudioSample*);
      auto in = (AudioSample **) malloc(in_size);

      ringBuf = jack_ringbuffer_create(
        info->nin * SAMPLE_SIZE * info->rbSize);

      /* Note from JACK sample capture_client.cpp:
       * When JACK is running realtime, jack_activate() will have
       * called mlockall() to lock our pages into memory.  But, we
       * still need to touch any newly allocated pages before
       * process() starts using them.  Otherwise, a page fault could
       * create a delay that would force JACK to shut us down.
       */
      memset(ringBuf->buf, 0, ringBuf->size);
      memset(in, 0, in_size);

      // Register input ports
      for (uint i = 0; i < info->nin; i++) {
        //TODO: replace std::string here
        std::string name = "input";
        name += std::to_string(i + 1);

        info->ports.in[i] = jack_port_register(
          info->client,
          name.c_str(),
          JACK_DEFAULT_AUDIO_TYPE,
          JackPortIsInput,
          0);
        if (info->ports.in[i] == NULL)
          LOGE << "Couldn't register port '" << name << "'";
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
      info->ports.outL = registerOutput("outLeft");
      info->ports.outR = registerOutput("outRight");

      // Find physical capture ports
      auto findPorts = [&](auto criteria, const char * type = "audio") {
        const char **ports = jack_get_ports(
          info->client,
          NULL,
          type,
          criteria);
        if (ports == NULL) {
          LOGF << "No ports found matching " << std::to_string(criteria);
          jack_client_close(info->client);
          exit(1);
        }
        return ports;
      };

      // Helper function for connections
      auto connectPort = [&](const char *src_name, const char *dest_name) {
        if (jack_connect(info->client, dest_name, src_name)) {
          LOGF << "Cannot connect port '" << src_name
          << "' to '" << dest_name << "'";
          LOGD << "src type: '" << jack_port_type(
            jack_port_by_name(client, src_name)) << "'";
          LOGD << "dest type: '" << jack_port_type(
            jack_port_by_name(client, dest_name)) << "'";
        }
      };

      const char **inputs  = findPorts(JackPortIsPhysical | JackPortIsOutput);
      const char **outputs = findPorts(JackPortIsPhysical | JackPortIsInput);

      uint ninputs = 0;
      while (inputs[ninputs] != NULL) ninputs++;
      uint noutputs = 0;
      while (outputs[noutputs] != NULL) noutputs++;

      for (uint i = 0; i < info->nin; i++) {
        connectPort(jack_port_name(info->ports.in[i]), inputs[i % ninputs]);
      }
      for (uint i = 0; i < info->nout; i++) {
        connectPort(outputs[i % noutputs], jack_port_name(info->ports.out[i]));
      }

      LOGI << "Connected ports, enabling canProcess";

      info->doProcess = 1;
    }

    int init (int argc, char *argv[]) {
      ThreadInfo info;
      memset(&info, 0, sizeof(info));

      client = jack_client_open(CLIENT_NAME, JackNullOption, &info.status);

      if (!(info.status & JackServerStarted)) {
        LOGF << "JACK server not running";
        exit(1);
      }

      LOGI << "JACK server started";
      LOGD << "JACK client status: " << info.status;

      info.client = client;
      info.doProcess = 0;

      jack_set_process_callback(client, process, &info);

      if (jack_activate(client)) LOGF << "Cannot activate JACK client";
      jack_activate(client);

      setupPorts(&info);

      while (1)
        sleep(10);

      jack_client_close(client);

      exit(0);
    }
  }
}

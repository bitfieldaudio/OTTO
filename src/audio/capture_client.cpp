/*
  Copyright (C) 2001 Paul Davis
  Copyright (C) 2003 Jack O'Quin

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  * 2002/08/23 - modify for libsndfile 1.0.0 <andy@alsaplayer.org>
  * 2003/05/26 - use ringbuffers - joq
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sndfile.h>
#include <pthread.h>
#include <signal.h>
#include <getopt.h>
#include <inttypes.h>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

namespace audio {
  namespace jack {
    namespace capture_client {

      typedef struct _thread_info {
        pthread_t thread_id;
        SNDFILE *sf;
        jack_nframes_t duration;
        jack_nframes_t rb_size;
        jack_client_t *client;
        unsigned int channels;
        int bitdepth;
        char *path;
        volatile int can_capture;
        volatile int can_process;
        volatile int status;
        volatile char recording;
      } jack_thread_info_t;

      /* JACK data */
      unsigned int nports;
      jack_port_t **ports;
      jack_default_audio_sample_t **in;
      jack_nframes_t nframes;
      const size_t sample_size = sizeof(jack_default_audio_sample_t);

      /* Synchronization between process thread and disk thread. */
#define DEFAULT_RB_SIZE 16384		/* ringbuffer size in frames */
      jack_ringbuffer_t *rb;
      pthread_mutex_t disk_thread_lock = PTHREAD_MUTEX_INITIALIZER;
      pthread_cond_t  data_ready = PTHREAD_COND_INITIALIZER;
      long overruns = 0;
      jack_client_t *client;

      void error (const char *desc) {
        fprintf(stderr, "JACK error: %s", desc);
      }

      static void signal_handler(int sig)
      {
        jack_client_close(client);
        fprintf(stderr, "signal received, exiting ...\n");
        exit(0);
      }

      static void *
      disk_thread (void *arg)
      {
        jack_thread_info_t *info = (jack_thread_info_t *) arg;
        static jack_nframes_t total_captured = 0;
        jack_nframes_t samples_per_frame = info->channels;
        size_t bytes_per_frame = samples_per_frame * sample_size;
        char *framebuf = (char*) malloc (bytes_per_frame);

        pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
        pthread_mutex_lock (&disk_thread_lock);

        info->status = 0;

        while (1) {

          /* Write the data one frame at a time.  This is
           * inefficient, but makes things simpler. */
          while (info->can_capture &&
                 (jack_ringbuffer_read_space (rb) >= bytes_per_frame)) {

            jack_ringbuffer_read (rb, framebuf, bytes_per_frame);

            if (sf_writef_float (info->sf, (jack_default_audio_sample_t *) framebuf, 1) != 1) {
              char errstr[256];
              sf_error_str (0, errstr, sizeof (errstr) - 1);
              fprintf (stderr,
                       "cannot write sndfile (%s)\n",
                       errstr);
              info->status = EIO; /* write failed */
              goto done;
            }

            if (++total_captured >= info->duration) {
              printf ("disk thread finished after %n frames\n", total_captured);
              goto done;
            }
          }

          /* wait until process() signals more data */
          pthread_cond_wait (&data_ready, &disk_thread_lock);
        }

      done:
        pthread_mutex_unlock (&disk_thread_lock);
        free (framebuf);
        return 0;
      }

      static int
      process (jack_nframes_t nframes, void *arg)
      {
        int chn;
        size_t i;
        jack_thread_info_t *info = (jack_thread_info_t *) arg;

        /* Do nothing until we're ready to begin. */
        if ((!info->can_process) || (!info->can_capture))
          return 0;

        for (chn = 0; chn < nports; chn++)
          in[chn] = (jack_default_audio_sample_t *) jack_port_get_buffer (ports[chn], nframes);

        /* Sndfile requires interleaved data.  It is simpler here to
         * just queue interleaved samples to a single ringbuffer. */
        for (i = 0; i < nframes; i++) {
          for (chn = 0; chn < nports; chn++) {
            if (jack_ringbuffer_write (rb, (char *) (in[chn]+i),
                                       sample_size)
                < sample_size)
              overruns++;
          }
        }

        /* Tell the disk thread there is work to do.  If it is already
         * running, the lock will not be available.  We can't wait
         * here in the process() thread, but we don't need to signal
         * in that case, because the disk thread will read all the
         * data queued before waiting again. */
        if (pthread_mutex_trylock (&disk_thread_lock) == 0) {
          pthread_cond_signal (&data_ready);
          pthread_mutex_unlock (&disk_thread_lock);
        }

        return 0;
      }

      static void
      jack_shutdown (void *arg)
      {
        fprintf(stderr, "JACK shut down, exiting ...\n");
        exit(1);
      }

      static void
      setup_disk_thread (jack_thread_info_t *info)
      {
        SF_INFO sf_info;
        int short_mask;

        sf_info.samplerate = jack_get_sample_rate (info->client);
        sf_info.channels = info->channels;

        switch (info->bitdepth) {
        case 8: short_mask = SF_FORMAT_PCM_U8;
          break;
        case 16: short_mask = SF_FORMAT_PCM_16;
          break;
        case 24: short_mask = SF_FORMAT_PCM_24;
          break;
        case 32: short_mask = SF_FORMAT_PCM_32;
          break;
        default: short_mask = SF_FORMAT_PCM_16;
          break;
        }
        sf_info.format = SF_FORMAT_WAV|short_mask;

        if ((info->sf = sf_open (info->path, SFM_WRITE, &sf_info)) == NULL) {
          char errstr[256];
          sf_error_str (0, errstr, sizeof (errstr) - 1);
          fprintf (stderr, "cannot open sndfile \"%s\" for output (%s)\n", info->path, errstr);
          jack_client_close (info->client);
          exit (1);
        }

        info->duration *= sf_info.samplerate;
        info->can_capture = 0;

        pthread_create (&info->thread_id, NULL, disk_thread, info);
      }

      static void
      run_disk_thread (jack_thread_info_t *info)
      {
        info->can_capture = 1;
        pthread_join (info->thread_id, NULL);
        sf_close (info->sf);
        if (overruns > 0) {
          fprintf (stderr,
                   "tapedeck failed with %ld overruns.\n", overruns);
          fprintf (stderr, " try a bigger buffer than -B %"
                   PRIu32 ".\n", info->rb_size);
          info->status = EPIPE;
        }
      }

      static void
      setup_ports (int sources, char *source_names[], jack_thread_info_t *info)
      {
        unsigned int i;
        size_t in_size;

        /* Allocate data structures that depend on the number of ports. */
        nports = sources;
        ports = (jack_port_t **) malloc (sizeof (jack_port_t *) * nports);
        in_size =  nports * sizeof (jack_default_audio_sample_t *);
        in = (jack_default_audio_sample_t **) malloc (in_size);
        rb = jack_ringbuffer_create (nports * sample_size * info->rb_size);

        /* When JACK is running realtime, jack_activate() will have
         * called mlockall() to lock our pages into memory.  But, we
         * still need to touch any newly allocated pages before
         * process() starts using them.  Otherwise, a page fault could
         * create a delay that would force JACK to shut us down. */
        memset(in, 0, in_size);
        memset(rb->buf, 0, rb->size);

        for (i = 0; i < nports; i++) {
          char name[64];

          sprintf (name, "input%d", i+1);

          if ((ports[i] = jack_port_register (info->client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0)) == 0) {
            fprintf (stderr, "cannot register input port \"%s\"!\n", name);
            jack_client_close (info->client);
            exit (1);
          }
        }

        const char **outputs;
        if ((outputs = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput)) == NULL) {
          error("Cannot find any physical capture ports");
          jack_client_close (info->client);
          exit(1);
        }

        for (i = 0; i < nports; i++) {
          if (jack_connect (info->client, outputs[0], jack_port_name (ports[i]))) {
            fprintf (stderr, "cannot connect input port %s to %s\n", jack_port_name (ports[i]), outputs[0]);
            jack_client_close (info->client);
            exit (1);
          }
        }

        info->can_process = 1;		/* process() can start, now */
      }

      int main (int argc, char *argv[]) {
        jack_thread_info_t thread_info;
        memset (&thread_info, 0, sizeof (thread_info));
        thread_info.rb_size = DEFAULT_RB_SIZE;
        opterr = 0;

        thread_info.path = "recording.wav";

        if ((client = jack_client_open ("tapedeck", JackNullOption, NULL)) == 0) {
          fprintf (stderr, "JACK server not running?\n");
          exit (1);
        }

        thread_info.duration = 10;
        thread_info.client = client;
        thread_info.channels = argc - optind;
        thread_info.can_process = 0;

        setup_disk_thread (&thread_info);

        jack_set_process_callback (client, process, &thread_info);
        jack_on_shutdown (client, jack_shutdown, &thread_info);

        if (jack_activate (client)) {
          fprintf (stderr, "cannot activate client");
        }

        setup_ports (argc - optind, &argv[optind], &thread_info);

        /* install a signal handler to properly quits jack client */
#ifndef WIN32
        signal(SIGQUIT, signal_handler);
        signal(SIGHUP, signal_handler);
#endif
        signal(SIGTERM, signal_handler);
        signal(SIGINT, signal_handler);

        run_disk_thread (&thread_info);

        jack_client_close (client);

        jack_ringbuffer_free (rb);

        exit (0);
      }

    }
  }
}

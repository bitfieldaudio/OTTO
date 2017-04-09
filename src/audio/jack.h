#pragma once

#include <cstdlib>
#include <string>

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.h>
#include <pthread.h>

#include "../events.h"

namespace audio {

typedef jack_default_audio_sample_t AudioSample;
const size_t SAMPLE_SIZE = sizeof(AudioSample);

namespace jack {
int init (int argc, char *argv[]);
}
}

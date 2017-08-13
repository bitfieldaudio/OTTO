#pragma once
#include "util/typedefs.hpp"

#include <type_traits>

namespace top1::audio {

/*
 * Mixes two signals, and normalizes the result.
 * Simple weighted average
 * @A Signal A
 * @B Signal B
 * @ratio B:A, amount of B to mix into signal A.
 */
inline float mix(float A, float B, float ratio = 0.5) {
  return A + (B - A) * ratio;
}

/*
 * A simple average, used to get a 1-dimensional graph of audio
 *
 */
struct Graph {
  float sum = 0;
  uint nsamples = 0;
  float average = 0;

  void add(float sample) {
    ++nsamples;
    sum += std::abs(sample);
    average = sum/nsamples;
  }
  void clear() {
    sum /= 16.0;
    nsamples /= 16;
    average = sum/nsamples;
  }

  float clip() const {
    return std::min<float>(average, 1);
  }

  operator float() {
    return average;
  }
};

/*
 * Audio Processors are anything that can process audio/midi.
 * They run on the audio thread, and are called by the audio system (Jack).
 * Formally, an audio processor is defined as having a method matching
 * this signature:
 *
 * ```
 * void process(ProcessData&);
 * ```
 *
 * This method _must_ not be called from anywhere other than the main
 * audio system and it's deligates.
 *
 * If another thread needs access to any of this data, e.g. the audio/midi data,
 * They need an audio processor to read it and store it. It is up to the module
 * in question to handle thread safety.
 */

/*
 * Checks if a type qualifies as an <AudioProcessor>
 */
template<typename...>
struct is_audio_processor {}; // TODO: Implementation

/*
 * A DynArray that resizes to fit the RealTime bufferSize.
 *
 * This is the container used in AudioProcessors, and it should be used
 * in any place where the realtime data is copied out. It is resized on
 * the bufferSizeChanged event
 */
template<typename T>
class RTBuffer : public top1::DynArray<T> {
public:

  using typename top1::DynArray<T>::value_type;
  using typename top1::DynArray<T>::size_type;
  using typename top1::DynArray<T>::difference_type;
  using typename top1::DynArray<T>::reference;
  using typename top1::DynArray<T>::const_reference;
  using typename top1::DynArray<T>::pointer;
  using typename top1::DynArray<T>::iterator;
  using typename top1::DynArray<T>::const_iterator;
  using typename top1::DynArray<T>::reverse_iterator;
  using typename top1::DynArray<T>::const_reverse_iterator;

  AudioBuffer(size_type sizeFactor = 1)
    : top1::DynArray<T>(0),
    sFactor (sizeFactor) {
    detail::registerAudioBufferResize([this] (uint newSize) {
       this->resize(newSize * sFactor);
     });
  }

  using top1::DynArray<T>::operator[];

private:
  size_type sFactor;
};

/*
 * Package of data passed to audio processors
 */
struct ProcessData {
  struct {
    // Sound data to the physical output
    AudioBuffer<float> outL;
    // Sound data to the physical output
    AudioBuffer<float> outR;
    // Sound data from the physical input
    AudioBuffer<float> input;
    // The sound that is passed between modules
    AudioBuffer<float> proc;
  } audioData;

  // Non-copyable
  ProcessData(&ProcessData) = delete;
  // Non-movable
  ProcessData(&&ProcessData) = delete;
}

namespace detail {
// to avoid circular deps
void registerAudioBufferResize(std::function<void(uint)>);
}

} // top1::audio

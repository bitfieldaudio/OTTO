#pragma once

#include <functional>
#include <gsl/span>

#include "core/audio/midi.hpp"

#include "util/dyn-array.hpp"
#include "util/audio.hpp"

namespace top1 {
  /**
     Audio Processors are anything that can process audio/midi.
     They run on the audio thread, and are called by the audio system (Jack).
     Formally, an audio processor is defined as having a method matching
     this signature:

     ```
     void process(const ProcessData&);
     ```

     This method _must_ not be called from anywhere other than the main
     audio system and it's deligates.

     If another thread needs access to any of this data, e.g. the audio/midi data,
     They need an audio processor to read it and store it. It is up to the module
     in question to handle thread safety.
  */
  namespace audio {

    /*
     * Checks if a type qualifies as an <AudioProcessor>
     */
    template<typename...>
    struct is_audio_processor {}; // TODO: Implementation


    namespace detail {
      // No including "core/globals.hpp" in headers
      void registerAudioBufferResize(std::function<void(uint)>);
    }

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

      RTBuffer(size_type sizeFactor = 1)
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
      struct Range {
        int i;
        int o;
      };
      struct AudioData {
        /// Sound data to the physical output
        gsl::span<float> outL;
        /// Sound data to the physical output
        gsl::span<float> outR;
        /// Sound data from the physical input
        gsl::span<float> input;
        /// The sound that is passed between modules
        gsl::span<float> proc;
        /// The location of the spans relative to the audio buffer
        ///
        /// Will mostly be zero, but is set on `slice`
        int offset;
      } audio;

      int nframes;
      // ProcessData is passed by const&, so this needs mutable
      // Maybe that is a bad idea?
      mutable std::vector<midi::MidiEventPtr> midi;

      ProcessData slice(Range bounds) const {
        int s = bounds.o - bounds.i;
        if (bounds.i < 0 || s > nframes) {
          throw "Illegal ProcessData slice";
        }
        ProcessData ret;
        ret.audio.offset += bounds.i;
        ret.nframes = s;
        ret.audio.outL  = {audio.outL.data() + bounds.i, s};
        ret.audio.outR  = {audio.outR.data() + bounds.i, s};
        ret.audio.input = {audio.input.data() + bounds.i, s};
        ret.audio.proc  = {audio.proc.data() + bounds.i, s};
        return ret;
      }
    };

  } // audio
} // top1

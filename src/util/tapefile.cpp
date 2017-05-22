#include "tapefile.h"

namespace top1 {

/****************************************/
/* TapeFile Implementation              */
/****************************************/

void TapeFile::readSlices() {
  slices.read(this);
}

void TapeFile::writeSlices() {
  slices.write(this);
}

void TapeFile::seek(int pos) {
  fseek(audioChunk.offset + 4 + pos);
}

uint TapeFile::write(AudioFrame* data, uint nframes) {
  try {
    writeBytes(data, nframes);
  } catch (ReadException e) {
    //LOGD << e.message;
    return 0;
  }
  uint newSize = wpos() - audioChunk.offset - 4;
  if (newSize > audioChunk.size) {
    audioChunk.size = newSize;
  }
  return nframes;
}

uint TapeFile::read(AudioFrame* data, uint nframes) {
  try {
    readBytes(data, nframes);
  } catch (ReadException e) {
    //LOGD << e.message;
    return 0;
  }
  return nframes;
}

}

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

}

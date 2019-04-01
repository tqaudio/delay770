#pragma once

#include <math.h>

namespace Delay770 {
class Buffer {
public:
  Buffer(int sampleRate, double capacity /* ms */);
  ~Buffer();

  void setDelayTime(double duration);

  double read();
  void write(double value);

protected:
  int mSampleRate; // e.g. 48000
  int mCapacity;   // e.g. 48000
  double mReadHead;
  int mWriteHead;
  double mInterval;
  double *mBuffer;
};
} // namespace Delay770

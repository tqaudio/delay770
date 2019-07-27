#include <math.h>

#include "../include/delaybuffer.h"

namespace Delay770 {
DelayBuffer::DelayBuffer(int sampleRate, double capacity /* ms */)
    : mSampleRate(sampleRate), mCapacity(sampleRate * capacity / 1000.0),
      mReadHead(0.0), mWriteHead(0), mInterval(0.0),
      mBuffer(new double[mCapacity]{}) {}

DelayBuffer::~DelayBuffer() { delete[] mBuffer; }

void DelayBuffer::setDelayTime(double duration) {
  mInterval = mSampleRate * duration / 1000.0;
}

double DelayBuffer::read() {
  mReadHead = (double)mWriteHead - mInterval;

  if (mReadHead < 0) {
    mReadHead += (double)mCapacity;
  }

  int index1 = floor(mReadHead);
  int index2 = (index1 + 1 > mCapacity - 1) ? 0 : index1 + 1;
  double value = mBuffer[index1] +
                 (mBuffer[index2] - mBuffer[index1]) * (mReadHead - index1);

  return value;
}

void DelayBuffer::write(double value) {
  mBuffer[mWriteHead] = value;

  mWriteHead += 1;

  if (mWriteHead > mCapacity - 1) {
    mWriteHead = 0;
  }
}
} // namespace Delay770

#include "../include/buffer.h"

namespace Delay770 {
Buffer::Buffer(int sampleRate, double capacity /* ms */)
    : mSampleRate(sampleRate), mCapacity(sampleRate * capacity / 1000.0f),
      mReadHead(0.0f), mWriteHead(0), mInterval(0.0f) {
  mBuffer = new double[mCapacity];

  for (int i = 0; i < mCapacity; i++) {
    mBuffer[i] = 0.0f;
  }
}

Buffer::~Buffer() { delete[] mBuffer; }

void Buffer::setDelayTime(double duration) {
  mInterval = mSampleRate * duration / 1000.0f;
}

double Buffer::read() {
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

void Buffer::write(double value) {
  mBuffer[mWriteHead] = value;

  mWriteHead += 1;

  if (mWriteHead > mCapacity - 1) {
    mWriteHead = 0;
  }
}
} // namespace Delay770

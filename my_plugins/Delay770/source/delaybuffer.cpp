#include <math.h>

#include "../include/delaybuffer.h"

namespace Delay770 {
DelayBuffer::DelayBuffer(int sampleRate /* Hz */, double maxDuration /* ms */,
                         double delayTime /* ms */)
    : mSampleRate(sampleRate), mCapacity(sampleRate * maxDuration / 1000.0),
      mMaxSample(sampleRate / 5), mBuffer(new double[mCapacity]{}) {
  mDelayTimes[0] = delayTime;
}

DelayBuffer::~DelayBuffer() { delete[] mBuffer; }

void DelayBuffer::setDelayTime(double delayTime /* ms */) {
  mTargetDelayTime = delayTime;
}

double DelayBuffer::read() {
  double values[2]{0.0, 0.0};

  for (int i = 0; i < 2; i++) {
    double distance = mDelayTimes[i] * mSampleRate / 1000.0;
    double readHead = static_cast<double>(mWriteHead) - distance;

    if (readHead < 0) {
      readHead += static_cast<double>(mCapacity);
    }

    int index1 = floor(readHead);
    int index2 = (index1 + 1 > mCapacity - 1) ? 0 : index1 + 1;
    double value = mBuffer[index1] +
                   (mBuffer[index2] - mBuffer[index1]) * (readHead - index1);

    values[i] = value;
  }

  return values[0] * mGains[0] + values[1] * mGains[1];
}

void DelayBuffer::write(double value) { mBuffer[mWriteHead] = value; }

void DelayBuffer::tick() {
  if (mTargetDelayTime != mCurrentDelayTime && mSampleCount == 0) {
    mTransition = true;
    mCurrentDelayTime = mTargetDelayTime;
    mDelayTimes[mMain ? 0 : 1] = mTargetDelayTime;
  }
  if (mTransition) {
    mSampleCount += 1;

    double gain = static_cast<double>(mSampleCount) / mMaxSample;
    mGains[mMain] = 1.0 - gain;
    mGains[mMain ? 0 : 1] = gain;
  }
  if (mSampleCount > mMaxSample) {
    mTransition = false;
    mSampleCount = 0;
    mMain = mMain ? 0 : 1;
  }

  mWriteHead += 1;

  if (mWriteHead > mCapacity - 1) {
    mWriteHead = 0;
  }
}
} // namespace Delay770

#pragma once

namespace Delay770 {
class DelayBuffer {
public:
  DelayBuffer(int sampleRate /* Hz */, double capacity /* ms */,
              double delayTime /* ms */);
  ~DelayBuffer();

  void setDelayTime(double duration);

  double read();
  void write(double value);
  void tick();

private:
  int mSampleRate; // e.g. 48000 (Hz)
  int mCapacity;   // e.g. 48000 (samples)
  double mReadHead = 0.0;
  int mWriteHead = 0;
  bool mTransition = false;
  int mSampleCount = 0;
  int mMaxSample; // e.g. 48000 (samples)
  int mMain = 0;
  double mDelayTimes[2] = {0.0, 0.0};
  double mGains[2] = {1.0, 0.0};
  double mTargetDelayTime;  // e.g. 100.0 (ms)
  double mCurrentDelayTime; // e.g. 100.0 (ms)
  double *mBuffer = nullptr;
};
} // namespace Delay770

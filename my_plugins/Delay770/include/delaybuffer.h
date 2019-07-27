#pragma once

namespace Delay770 {
class DelayBuffer {
public:
  DelayBuffer(int sampleRate, double capacity /* ms */);
  ~DelayBuffer();

  void setDelayTime(double duration);

  double read();
  void write(double value);

private:
  int mSampleRate; // e.g. 48000 (Hz)
  int mCapacity;   // e.g. 48000 (samples)
  double mReadHead;
  int mWriteHead;
  double mInterval;
  double *mBuffer;
};
} // namespace Delay770

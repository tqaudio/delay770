#include "../include/parameter.h"

namespace Delay770 {
GainParameter::GainParameter(const char *title, int32 flags, int32 id) {
  UString(info.title, USTRINGSIZE(info.title)).fromAscii(title);
  UString(info.units, USTRINGSIZE(info.units)).fromAscii("dB");
  info.flags = flags;
  info.id = id;
  info.stepCount = 0;
  info.unitId = kRootUnitId;
}

void GainParameter::toString(ParamValue normValue, String128 text) const {
  char buffer[32];

  if (normValue > 0.0f) {
    double db = 20 * log10f(normValue);
    sprintf(buffer, "%.2f", db);
  } else {
    strcpy(buffer, "-infinity");
  }

  UString(text, 128).fromAscii(buffer);
}

bool GainParameter::fromString(const TChar *text, ParamValue &normValue) const {
  double gain = 0.0f;
  char buffer[32];
  UString wrapper((TChar *)text, -1);
  wrapper.toAscii(buffer, 32);

  if (strcmp(buffer, "-oo") == 0 || strcmp(buffer, "-infinity") == 0) {
    normValue = 0;
    return true;
  }
  if (!wrapper.scanFloat(gain)) {
    normValue = 0.0f;
    return true;
  }
  if (gain > 0.0) {
    gain = -gain;
  }

  normValue = expf(logf(10.0f) * gain / 20.0f);

  return true;
}

LinearParameter::LinearParameter(const char *title, const char *unit,
                                 double maxValue, int32 precision, int32 flags,
                                 int32 id)
    : mMaxValue(maxValue), mPrecision(precision) {
  UString(info.title, USTRINGSIZE(info.title)).fromAscii(title);
  UString(info.units, USTRINGSIZE(info.units)).fromAscii(unit);
  info.flags = flags;
  info.id = id;
  info.stepCount = 0;
  info.unitId = kRootUnitId;
}

void LinearParameter::toString(ParamValue normValue, String128 text) const {
  UString(text, 128).printFloat(normValue * mMaxValue, mPrecision);
}

bool LinearParameter::fromString(const TChar *text,
                                 ParamValue &normValue) const {
  double value = 0.0f;
  UString wrapper((TChar *)text, -1);

  if (!wrapper.scanFloat(value)) {
    return false;
  }
  if (value < 0.0f) {
    value = 0.0f;
  }
  if (value > mMaxValue) {
    value = mMaxValue;
  }

  normValue = value / mMaxValue;

  return true;
}
} // namespace Delay770

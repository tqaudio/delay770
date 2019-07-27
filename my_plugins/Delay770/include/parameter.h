#pragma once

#include "pluginterfaces/base/ustring.h"
#include "public.sdk/source/vst/vsteditcontroller.h"
#include <string.h>

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace Delay770 {
enum Parameters : ParamID {
  kBypassId = 100,
  kDelayTimeId = 101,
  kFeedbackId = 102,
  kDryId = 103,
  kWetId = 104
};

struct AutomationParameter {
  ParamValue value = 0.0;
  bool hasChanged = false;
};

class GainParameter : public Parameter {
public:
  GainParameter(const char *title, int32 flags, int32 id);
  void toString(ParamValue normValue, String128 string) const SMTG_OVERRIDE;
  bool fromString(const TChar *string,
                  ParamValue &normValue) const SMTG_OVERRIDE;
};

class LinearParameter : public Parameter {
public:
  LinearParameter(const char *title, const char *unit, double maxValue,
                  int32 precision, int32 flags, int32 id);
  void toString(ParamValue normValue, String128 text) const SMTG_OVERRIDE;
  bool fromString(const TChar *string,
                  ParamValue &normValue) const SMTG_OVERRIDE;

private:
  double mMaxValue;
  int32 mPrecision;
};
} // namespace Delay770

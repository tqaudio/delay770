#pragma once

#define MAX_DURATION 1000.0f      /* ms */

#define DEFAULT_DELAY_TIME 189.0f /* ms */
#define DEFAULT_DELAY_TIME_NORMALIZED DEFAULT_DELAY_TIME / MAX_DURATION

#define DEFAULT_FEEDBACK -7.56f /* dB */
#define DEFAULT_FEEDBACK_NORMALIZED expf(logf(10.0f) * DEFAULT_FEEDBACK / 20.0f)

#define DEFAULT_DRY 0.0f /* dB */
#define DEFAULT_DRY_NORMALIZED expf(logf(10.0f) * DEFAULT_DRY / 20.0f)

#define DEFAULT_WET -16.0f /* dB */
#define DEFAULT_WET_NORMALIZED expf(logf(10.0f) * DEFAULT_WET / 20.0f)

#include "pluginterfaces/base/ustring.h"
#include "public.sdk/source/vst/vsteditcontroller.h"
#include <math.h>
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
public:
  ParamValue value;
  bool hasChanged;
  AutomationParameter() : value(0.0f), hasChanged(false){};
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

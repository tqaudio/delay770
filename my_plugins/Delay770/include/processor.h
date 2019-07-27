#pragma once
#include <math.h>

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

#include "constants.h"
#include "delaybuffer.h"
#include "id.h"
#include "parameter.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace Delay770 {
class Processor : public AudioEffect {
public:
  static FUnknown *createInstance(void *) {
    return (IAudioProcessor *)new Processor();
  }

  Processor();

  tresult PLUGIN_API initialize(FUnknown *context) SMTG_OVERRIDE;
  tresult PLUGIN_API setBusArrangements(SpeakerArrangement *inputs,
                                        int32 numIns,
                                        SpeakerArrangement *outputs,
                                        int32 numOuts) SMTG_OVERRIDE;

  tresult PLUGIN_API setupProcessing(ProcessSetup &newSetup) SMTG_OVERRIDE;
  tresult PLUGIN_API setActive(TBool state) SMTG_OVERRIDE;
  tresult PLUGIN_API process(ProcessData &data) SMTG_OVERRIDE;

  tresult PLUGIN_API setState(IBStream *state) SMTG_OVERRIDE;
  tresult PLUGIN_API getState(IBStream *state) SMTG_OVERRIDE;

private:
  DelayBuffer **mDelayBuffer = nullptr;

  AutomationParameter *mDelayTimes = nullptr;
  AutomationParameter *mFeedbacks = nullptr;
  AutomationParameter *mDries = nullptr;
  AutomationParameter *mWets = nullptr;

  bool mBypass = false;
  ParamValue mDelayTime = Constants::defaultDelayTime / Constants::maxDelayTime;
  ParamValue mFeedback = exp(log(10.0) * Constants::defaultFeedback / 20.0);
  ParamValue mDry = exp(log(10.0) * Constants::defaultDry / 20.0);
  ParamValue mWet = exp(log(10.0) * Constants::defaultWet / 20.0);
};
} // namespace Delay770

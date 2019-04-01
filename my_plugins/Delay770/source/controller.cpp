#include "../include/controller.h"

namespace Delay770 {
tresult PLUGIN_API Controller::initialize(FUnknown *context) {
  tresult result = EditController::initialize(context);

  if (result != kResultOk) {
    return result;
  }

  parameters.addParameter(STR16("Bypass"), 0, 1, 0,
                          ParameterInfo::kCanAutomate |
                              ParameterInfo::kIsBypass,
                          Parameters::kBypassId);

  LinearParameter *delayTime = new LinearParameter(
      "Delay Time", "ms", 1000.0f, 2, ParameterInfo::kCanAutomate,
      Parameters::kDelayTimeId);
  parameters.addParameter(delayTime);

  GainParameter *feedback = new GainParameter(
      "Feedback", ParameterInfo::kCanAutomate, Parameters::kFeedbackId);
  parameters.addParameter(feedback);

  GainParameter *dry =
      new GainParameter("Dry", ParameterInfo::kCanAutomate, Parameters::kDryId);
  parameters.addParameter(dry);

  GainParameter *wet =
      new GainParameter("Wet", ParameterInfo::kCanAutomate, Parameters::kWetId);
  parameters.addParameter(wet);

  return result;
}

tresult PLUGIN_API Controller::setComponentState(IBStream *state) {
  if (!state) {
    return kResultFalse;
  }

  IBStreamer streamer(state, kLittleEndian);
  int32 savedBypass;
  float savedDelayTime = 0.0f;
  float savedFeedback = 0.0f;
  float savedDry = 0.0f;
  float savedWet = 0.0f;

  if (!streamer.readInt32(savedBypass)) {
    return kResultFalse;
  }
  if (!streamer.readFloat(savedDelayTime)) {
    return kResultFalse;
  }
  if (!streamer.readFloat(savedFeedback)) {
    return kResultFalse;
  }
  if (!streamer.readFloat(savedDry)) {
    return kResultFalse;
  }
  if (!streamer.readFloat(savedWet)) {
    return kResultFalse;
  }

  setParamNormalized(Parameters::kBypassId, savedBypass ? 1 : 0);
  setParamNormalized(Parameters::kDelayTimeId, savedDelayTime);
  setParamNormalized(Parameters::kFeedbackId, savedFeedback);
  setParamNormalized(Parameters::kDryId, savedDry);
  setParamNormalized(Parameters::kWetId, savedWet);

  return kResultOk;
}

IPlugView *PLUGIN_API Controller::createView(const char *name) {
  if (name && strcmp(name, "editor") == 0) {
    auto *view = new VST3Editor(this, "Delay770", "main.uidesc");
    return view;
  }
  return nullptr;
}
} // namespace Delay770

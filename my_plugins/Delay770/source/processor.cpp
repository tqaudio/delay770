#include "../include/processor.h"

namespace Delay770 {
Processor::Processor()
    : mBypass(false), mDelayTime(DEFAULT_DELAY_TIME_NORMALIZED),
      mFeedback(DEFAULT_FEEDBACK_NORMALIZED), mDry(DEFAULT_DRY_NORMALIZED),
      mWet(DEFAULT_WET_NORMALIZED) {
  setControllerClass(ControllerID);
}

tresult PLUGIN_API Processor::initialize(FUnknown *context) {
  tresult result = AudioEffect::initialize(context);

  if (result != kResultTrue) {
    return kResultFalse;
  }

  addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
  addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

  return kResultTrue;
}

tresult PLUGIN_API Processor::setBusArrangements(SpeakerArrangement *inputs,
                                                 int32 numIns,
                                                 SpeakerArrangement *outputs,
                                                 int32 numOuts) {
  if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0]) {
    return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
  }

  return kResultFalse;
}

tresult PLUGIN_API Processor::setupProcessing(ProcessSetup &newSetup) {
  return AudioEffect::setupProcessing(newSetup);
}

tresult PLUGIN_API Processor::setActive(TBool state) {
  SpeakerArrangement arrangement;

  if (getBusArrangement(kOutput, 0, arrangement) != kResultTrue) {
    return kResultFalse;
  }

  int channelCount = SpeakerArr::getChannelCount(arrangement);

  if (channelCount != 2) {
    return kResultFalse;
  }
  if (state) {
    for (int channel = 0; channel < channelCount; channel++) {
      mBuffer[channel] = new Buffer(processSetup.sampleRate, MAX_DURATION);
      mBuffer[channel]->setDelayTime(mDelayTime * MAX_DURATION);
    }
    mDelayTimes = new AutomationParameter[processSetup.maxSamplesPerBlock];
    mFeedbacks = new AutomationParameter[processSetup.maxSamplesPerBlock];
    mDries = new AutomationParameter[processSetup.maxSamplesPerBlock];
    mWets = new AutomationParameter[processSetup.maxSamplesPerBlock];
  } else {
    for (int channel = 0; channel < channelCount; channel++) {
      delete mBuffer[channel];
    }
    delete mDelayTimes;
    delete mFeedbacks;
    delete mDries;
    delete mWets;
  }

  return AudioEffect::setActive(state);
}

tresult PLUGIN_API Processor::process(ProcessData &data) {
  if (data.inputParameterChanges) {
    int32 numParamsChanged = data.inputParameterChanges->getParameterCount();

    for (int32 index = 0; index < numParamsChanged; index++) {
      IParamValueQueue *paramQueue =
          data.inputParameterChanges->getParameterData(index);

      if (paramQueue == nullptr) {
        continue;
      }

      int32 numPoints = paramQueue->getPointCount();
      int32 sampleOffset;
      ParamValue value;

      if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) !=
          kResultTrue) {
        continue;
      }
      if (sampleOffset < 0) {
        sampleOffset = 0;
      }
      if (sampleOffset > data.numSamples - 1) {
        sampleOffset = data.numSamples - 1;
      }
      switch (paramQueue->getParameterId()) {
      case Parameters::kBypassId:
        mBypass = (value > 0.5f);
        break;
      case Parameters::kDelayTimeId:
        mDelayTime = value;
        mDelayTimes[sampleOffset].value = value;
        mDelayTimes[sampleOffset].hasChanged = true;
        break;
      case Parameters::kFeedbackId:
        mFeedback = value;
        mFeedbacks[sampleOffset].value = value;
        mFeedbacks[sampleOffset].hasChanged = true;
        break;
      case Parameters::kDryId:
        mDry = value;
        mDries[sampleOffset].value = value;
        mDries[sampleOffset].hasChanged = true;
        break;
      case Parameters::kWetId:
        mWet = value;
        mWets[sampleOffset].value = value;
        mWets[sampleOffset].hasChanged = true;
        break;
      }
    }
  }
  if (data.numInputs == 0 || data.numOutputs == 0) {
    return kResultOk;
  }
  if (data.numSamples > 0) {
    SpeakerArrangement arrangement;
    getBusArrangement(kOutput, 0, arrangement);
    int32 channelCount = SpeakerArr::getChannelCount(arrangement);
    float *inputChannel = nullptr;
    float *outputChannel = nullptr;

    for (int32 sample = 0; sample < data.numSamples; sample++) {
      for (int32 channel = 0; channel < channelCount; channel++) {
        inputChannel = data.inputs[0].channelBuffers32[channel];
        outputChannel = data.outputs[0].channelBuffers32[channel];

        if (mDelayTimes[sample].hasChanged) {
          mBuffer[channel]->setDelayTime(mDelayTimes[sample].value *
                                         MAX_DURATION);
          if (channel == channelCount - 1) {
            mDelayTimes[sample].hasChanged = false;
          }
        }
        if (mFeedbacks[sample].hasChanged) {
          mFeedback = mFeedbacks[sample].value;
          if (channel == channelCount - 1) {
            mFeedbacks[sample].hasChanged = false;
          }
        }
        if (mDries[sample].hasChanged) {
          mDry = mDries[sample].value;
          if (channel == channelCount - 1) {
            mDries[sample].hasChanged = false;
          }
        }
        if (mWets[sample].hasChanged) {
          mWet = mWets[sample].value;
          if (channel == channelCount - 1) {
            mWets[sample].hasChanged = false;
          }
        }

        float delay = mBuffer[channel]->read();
        outputChannel[sample] = delay * mWet + inputChannel[sample] * mDry;
        mBuffer[channel]->write(inputChannel[sample] + delay * mFeedback);
      }
    }
  }

  return kResultOk;
}

tresult PLUGIN_API Processor::setState(IBStream *state) {
  if (!state) {
    return kResultFalse;
  }

  IBStreamer streamer(state, kLittleEndian);
  int32 savedBypass = 0;
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

  mBypass = savedBypass > 0;
  mDelayTime = savedDelayTime;
  mFeedback = savedFeedback;
  mDry = savedDry;
  mWet = savedWet;

  return kResultOk;
}

tresult PLUGIN_API Processor::getState(IBStream *state) {
  IBStreamer streamer(state, kLittleEndian);
  int32 saveBypass = mBypass ? 1 : 0;
  float saveDelayTime = mDelayTime;
  float saveFeedback = mFeedback;
  float saveDry = mDry;
  float saveWet = mWet;

  streamer.writeInt32(saveBypass);
  streamer.writeFloat(saveDelayTime);
  streamer.writeFloat(saveFeedback);
  streamer.writeFloat(saveDry);
  streamer.writeFloat(saveWet);

  return kResultOk;
}
} // namespace Delay770

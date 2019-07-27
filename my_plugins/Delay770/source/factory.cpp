#include "pluginterfaces/base/fplatform.h"
#include "public.sdk/source/main/pluginfactory.h"

#include "../include/controller.h"
#include "../include/id.h"
#include "../include/processor.h"

#define MAJOR_VERSION_STR "0"
#define MAJOR_VERSION_INT 0

#define SUB_VERSION_STR "2"
#define SUB_VERSION_INT 2

#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT 0

#define BUILD_NUMBER_STR "2"
#define BUILD_NUMBER_INT 2

#define FULL_VERSION_STR                                                       \
  MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR                 \
                    "." BUILD_NUMBER_STR
#define VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR

#define stringPluginName "Delay770"
#define stringOriginalFilename "Delay770.vst3"

#if SMTG_PLATFORM_64
#define stringFileDescription stringPluginName " (64 bit)"
#else
#define stringFileDescription stringPluginName " (32 bit)"
#endif

#define stringCompanyName "TQ Audio\0"
#define stringCompanyWeb "https://github.com/tqaudio/delay770"
#define stringCompanyEmail "mailto:moutend@gmail.com"
#define stringLegalCopyright "(c) 2019 TQ Audio"

#define stringLegalTrademarks                                                  \
  "VST is a trademark of Steinberg Media Technologies GmbH"

BEGIN_FACTORY_DEF(stringCompanyName, stringCompanyWeb, stringCompanyEmail)
DEF_CLASS2(INLINE_UID_FROM_FUID(Delay770::ProcessorID),
           PClassInfo::kManyInstances, kVstAudioEffectClass, stringPluginName,
           Vst::kDistributable, Vst::PlugType::kFx, FULL_VERSION_STR,
           kVstVersionString, Delay770::Processor::createInstance)
DEF_CLASS2(INLINE_UID_FROM_FUID(Delay770::ControllerID),
           PClassInfo::kManyInstances, kVstComponentControllerClass,
           stringPluginName "Controller", 0, "", FULL_VERSION_STR,
           kVstVersionString, Delay770::Controller::createInstance)
END_FACTORY

bool InitModule() { return true; }
bool DeinitModule() { return true; }

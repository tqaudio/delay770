#pragma once

#include "pluginterfaces/base/fplatform.h"

#define MAJOR_VERSION_STR "0"
#define MAJOR_VERSION_INT 0

#define SUB_VERSION_STR "1"
#define SUB_VERSION_INT 1

#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT 0

#define BUILD_NUMBER_STR "1"
#define BUILD_NUMBER_INT 1

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

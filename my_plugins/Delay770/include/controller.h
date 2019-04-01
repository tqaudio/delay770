#pragma once

#include "id.h"
#include "parameter.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "public.sdk/source/vst/vsteditcontroller.h"
#include "vstgui/plugin-bindings/vst3editor.h"

using namespace Steinberg;
using namespace Steinberg::Vst;
using namespace VSTGUI;

namespace Delay770 {
class Controller : public EditController, public VST3EditorDelegate {
public:
  static FUnknown *createInstance(void *) {
    return (IEditController *)new Controller();
  }

  tresult PLUGIN_API initialize(FUnknown *context) SMTG_OVERRIDE;
  tresult PLUGIN_API setComponentState(IBStream *state) SMTG_OVERRIDE;
  IPlugView *PLUGIN_API createView(const char *name);
};
} // namespace Delay770

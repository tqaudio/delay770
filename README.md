Delay770
========

[![VST3: YES](https://img.shields.io/badge/VST3-YES-blue.svg)](https://www.steinberg.net/en/company/technologies/vst3.html)
[![AUv2: YES](https://img.shields.io/badge/AUv2-YES-blue.svg)](https://developer.apple.com/documentation/audiounit)
[![AAX: NO](https://img.shields.io/badge/AAX-NO-red.svg)](http://apps.avid.com/aax-portal/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

![Delay770 snapshot](https://tqaudio.github.io/img/delay770.png)

The Delay770 is a feedback delay plugin.

To install the plugin, visit the [TQ Audio website](https://tqaudio.github.io/products/delay770) and follow the instruction.

----------------

- VST is a trademark of Steinberg Media Technologies GmbH, registered in Europe and other countries.
- Audio Unit is a trademark of Apple Inc.
- AAX is a trademark of Avid Technology.

## Develop

The VST3 plugin development is not easy but not hard. Let's clone this repository and start developing today.

### Prerequisites

You need the following tools:

- Common to Windows and Mac
  - [git v1.5.3 or later](https://git-scm.com/downloads)
  - [cmake v3.4.3 or later](https://cmake.org/download/)
  - clang-format (optional)
- Windows
  - VisualStudio 2015 or 2017
- Mac
  - Xcode 10.0 or later

### Build

Launch the console, `cmd.exe` on Windows or 'Terminal.app` on Mac. Then run the following commands:

```console
git clone https://github.com/tqaudio/delay770.git
cd delay770
git submodule update --init --recursive
mkdir build
cd build
```

Finally, run the build command depends on each platforms.

#### Windows

```console
..\tools\windows_setup.bat
msbuild vstsdk.sln
```

That's it! If the build succeeds, `VST3` folder will be generated.

Note: You should use the developer command prompt, not a normal `cmd.exe`. The developer command prompt comes with the VisualStudio installation. Hit the Windows key and then type "dev" or "developer" to launch.

#### Mac

```console
../tools/darwin_setup.bash
xcodebuild
```

That's it! If the build succeeds, `VST3` folder will be generated.

### Audio Unit and AAX

To build the Audio Unit and AAX version of this plugin, see `AUv2.md` and `AAX.md` respectively.

### Pull request or fork?

This repository accepts only the pull requests such as bug fix. If you want to add new features to the plugin, fork and start developing your own plugin.

## LICENSE

See LICENSE.

## Author

[Yoshiyuki Koyanagi <moutend@gmail.com>](https://github.com/moutend)

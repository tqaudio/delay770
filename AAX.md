Setup AAX
=========

The guide to the build the AAX format of the plugin.

Note: AAX support is experimental. You can build the plugin, but can't load.

## Prerequisites

Before you begin, confirm the VST3 version of this plugin can build.

## Build

To download the AAX SDK, you need register an AVID MASTER ACCOUNT at first.

Next, download the [AAX SDK v2.3.1](https://www.avid.com/alliance-partner-program/aax-connectivity-toolkit) from AVID's website.

After download the SDK, run the following commands:

```console
unzip ./AAX_SDK_2p3p1.zip
cp -r ./AAX_SDK_2p3p1 /path/to/delay770/external.avid.aax
cd /path/to/delay770/build
../tools/darwin_setup.bash # Mac
..\tools\windows_setup.bat # Windows
```

FYI, `unzip`, `cp` and `file` commands are comes with git installation on Windows.

You'll see the following messages when the AAX SDK is detected:

```console
...
-- SMTG_AAX_SDK_PATH is set to : /Users/tqaudio/develop/delay770/vst3sdk/../external.avid.aax
* To enable building the InterAppAudio NoteExpressionSynth example for iOS you need to set the SMTG_IOS_DEVELOPMENT_TEAM and use the Xcode generator
* To enable building the AUv3 Wrapper example for iOS you need to set the SMTG_IOS_DEVELOPMENT_TEAM and use the Xcode generator
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/tqaudio/develop/delay770/build
```

Then run the build command depends on each platforms.

**Windows**

```console
msbuild *.sln
```

**Mac**

```console
xcodebuild
```

That's it! If the build succeeds,`AAXPlugin` folder will be generated.

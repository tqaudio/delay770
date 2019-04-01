Setup Audio Unit v2
===================

The guide to the build the Audio Unit v2 format of the plugin.

Note: Audio Unit v3 is not supported yet.

## Prerequisites

Before you begin, confirm the VST3 version of this plugin can build.

## Build

Download the [Core Audio SDK v1.1](https://developer.apple.com/library/archive/samplecode/CoreAudioUtilityClasses/Introduction/Intro.html) from Apple's website.

After download the SDK, run the following commands:

```console
unzip ./CoreAudioUtilityClasses.zip
cp -r ./CoreAudioUtilityClasses/CoreAudio /path/to/delay770
cd /path/to/delay770/build
../tools/darwin_setup.bash
```

You'll see the following messages when the Core Audio SDK is detected:

```console
...
-- SMTG_COREAUDIO_SDK_PATH is set to : /Users/tqaudio/develop/delay770/vst3sdk/../CoreAudio
-- SMTG_AAX_SDK_PATH is not set. If you need it, please download the AAX SDK!
* To enable building the InterAppAudio NoteExpressionSynth example for iOS you need to set the SMTG_IOS_DEVELOPMENT_TEAM and use the Xcode generator
* To enable building the AUv3 Wrapper example for iOS you need to set the SMTG_IOS_DEVELOPMENT_TEAM and use the Xcode generator
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/tqaudio/develop/delay770/build
```

Run the following command:

```console
xcodebuild
```

That's it! The `Delay770auv2.component` will be generated When the build successfully done.

## Install

Run the following command:

```console
sudo cp -r ./VST3/Debug/Delay770auv2.component /Library/Audio/Plug-Ins/Components
```

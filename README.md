**PowerAudio fork of Odin 2**

This fork of Odin 2 has the following changes:

* The plugin is built with [a fork of JUCE] that includes fixes for IBM Power.
* Added installation rules so the plugin can be installed with
  `cmake --install` or `make install`.
* In the [`lv2-only`] branch, added CMake option `LV2_ONLY` to build the plugin
  only as LV2.

[a fork of JUCE]: https://github.com/poweraudio/lpp-juce
[`lv2-only`]: https://github.com/poweraudio/odin2/tree/lv2-only

---

|Master|Devel|
|---|---|
|[![Build Status](https://dev.azure.com/TheWaveWarden/odin2/_apis/build/status/TheWaveWarden.odin2?branchName=master)](https://dev.azure.com/TheWaveWarden/odin2/_build/latest?definitionId=1&branchName=master)|[![Build Status](https://dev.azure.com/TheWaveWarden/odin2/_apis/build/status/TheWaveWarden.odin2?branchName=devel)](https://dev.azure.com/TheWaveWarden/odin2/_build/latest?definitionId=1&branchName=devel)|

# Odin 2 Synthesizer

This is the home of **Odin 2 free VST3, CLAP, AU and LV2 synthesizer** plugin. This repository contains the code to build the project. **If you just want to download the synth, get it from
https://thewavewarden.com/odin2**

![alt text](screenshot.png)

# Build Instructions

## Prerequisites
You'll need [CMake](https://cmake.org/download/) version 3.17 or higher to build Odin 2. On Linux systems, you'll likely need more prerequisites, see Linux below.

## All Platforms
Clone this project **with submodules**:
```
git clone --recurse-submodules https://github.com/TheWaveWarden/odin2.git
```
Now navigate into the repository and generate the build files with CMake:
```
cmake -B build -D CMAKE_BUILD_TYPE=Release
```
Finally, build the project:
```
cmake --build build --config Release
```
To build in debug configuration instead, replace `Release` with `Debug` in the above commands.
After a successfull build, you will find the compiled binaries in
```
build/Odin2_artefacts/Release/
```

## Linux Prerequisites
Upon building the project, you will most likely hit some errors regarding missing header files. You need to find out which packages the header belongs to and install the required packages. On Ubuntu 18.04, the required packages can be installed with
```
sudo apt install libx11-dev libwebkit2gtk-4.0-dev mesa-common-dev libasound2-dev libcurl4-gnutls-dev libcurl4-gnutls-dev
```

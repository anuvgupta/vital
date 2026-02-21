# Vital AI Agent

This is a fork of the open source synthesizer Vital (at version 1.0.6 or 1.0.7).

This fork adds an AI agentic sidepanel to Vital.

## Demos

### 1/30/2026

[![Video Title](https://markdown-videos.vercel.app/youtube/GkKuZN7fDMQ)](https://www.youtube.com/watch?v=GkKuZN7fDMQ)



## Building from Source

### Cross-Platform Build Script

The easiest way to build is using the unified build script, which auto-detects your platform:

```bash
./build.sh                    # Debug build
./build.sh --config=Release   # Release build
```

This script detects macOS, Windows (Git Bash/WSL), or Linux and runs the appropriate platform-specific build script.

### macOS

**Dependencies:**
- **Xcode** - Install from the Mac App Store or [developer.apple.com](https://developer.apple.com/xcode/)
- **Xcode Command Line Tools** - Run `xcode-select --install`
- **JUCE/Projucer** - Download from [juce.com](https://juce.com/get-juce/) (used to generate Xcode project)

**Build:**
```bash
./build_macos.sh
```

Options:
- `--config=Debug|Release` - Build configuration (default: Debug)
- `--skip-regenerate` - Skip Xcode project regeneration (faster rebuilds)
- `--no-run` - Build only, don't launch the app
- `--clean` - Clean build before building

### Windows

**Dependencies:**
- **Visual Studio 2019** (or 2017) - Install with "Desktop development with C++" workload from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/downloads/)
- **Intel oneAPI Base Toolkit** - Required for Intel IPP (fast FFT). Download from [intel.com](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html)
- **JUCE/Projucer** - Download from [juce.com](https://juce.com/get-juce/) (used to generate VS project)

**Build (from Command Prompt or PowerShell):**
```cmd
build_windows.bat
```

Or from Git Bash/WSL:
```bash
./build.sh
```

Options:
- `--config=Debug|Release` - Build configuration (default: Debug)
- `--skip-regenerate` - Skip VS project regeneration (faster rebuilds)
- `--no-run` - Build only, don't launch the app
- `--clean` - Clean build before building

### Linux

**Dependencies:**
- **GCC/G++** - `sudo apt install build-essential`
- **JUCE dependencies** - `sudo apt install libasound2-dev libcurl4-openssl-dev libfreetype6-dev libgl1-mesa-dev libx11-dev libxcomposite-dev libxcursor-dev libxinerama-dev libxrandr-dev`
- **JUCE/Projucer** - Download from [juce.com](https://juce.com/get-juce/) or build from source
    - Download and extract JUCE to `~/JUCE`
    - Build Projucer with `cd ~/JUCE/extras/Projucer/Builds/LinuxMakefile` and `make CONFIG=Release`
    - The Projucer binary will be in: `~/JUCE/extras/Projucer/Builds/LinuxMakefile/build/Projucer`
    - Optional: Create a symlink for easy access: `sudo ln -s ~/JUCE/extras/Projucer/Builds/LinuxMakefile/build/Projucer /usr/local/bin/Projucer`

**Debian/Ubuntu:**
```bash
sudo apt install build-essential pkg-config libasound2-dev libfreetype6-dev \
    libcurl4-openssl-dev libsecret-1-dev libglib2.0-dev libgl1-mesa-dev \
    libfftw3-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev
```

(Raspberry Pi)
```bash
sudo apt-get install -y \
  git build-essential pkg-config \
  libasound2-dev \
  libfreetype6-dev \
  libfontconfig1-dev \
  libx11-dev \
  libxcomposite-dev \
  libxcursor-dev \
  libxext-dev \
  libxinerama-dev \
  libxrandr-dev \
  libxrender-dev \
  libwebkit2gtk-4.0-dev \
  libglu1-mesa-dev \
  mesa-common-dev \
  libjack-jackd2-dev
``

**Fedora/RHEL:**
```bash
sudo dnf install gcc-c++ make pkg-config alsa-lib-devel freetype-devel \
    libcurl-devel libsecret-devel glib2-devel mesa-libGL-devel \
    fftw-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel
```

**Build:**
```bash
./build_linux.sh
```

Options:
- `--config=Debug|Release` - Build configuration (default: Debug)
- `--skip-regenerate` - Skip Makefile regeneration (faster rebuilds)
- `--no-run` - Build only, don't launch the app
- `--clean` - Clean build before building

## Developer Information

- Steering doc is `STEERING.md`
    - `CLAUDE.md` and `AGENTS.md` are symlinks to `STEERING.md` created with `ln -s` on macOS. Be careful on Windows.
- Additional agent config is in `./agents`

## Vital (Original Readme)

Vital is a spectral warping wavetable synthesizer. This is the source.

This repository is updated on a delay after binary releases.

### Code Licensing

If you are making a proprietary or closed source app and would like to use Vital's source code, contact licensing@vital.audio for non GPLv3 licensing options.

### Installing

Create an account and download Vital at [vital.audio](https://vital.audio)

### Issues

Report bugs (e.g.non-code and non-compiling issues) to https://forum.vital.audio

Feel free to report issues on building/compiling here but note that I'm not prioritizing them.

### Pull requests

I will not take any pull requests.

### What can you do with the source

The source code is licensed under the GPLv3. If you download the source or create builds you must comply with that license.

#### Things you can't do with this source

- Do not create an app and distribute it on the iOS app store. The app store is not comptabile with GPLv3 and you'll only get an exception for this if you're paying for a GPLv3 exception for Vital's source (see Code Licensing above).
- Do not use the name "Vital", "Vital Audio", "Tytel" or "Matt Tytel" for marketing or to name any distribution of binaries built with this source. This source code does not give you rights to infringe on trademarks.
- Do not connect to any web service at https://vital.audio, https://account.vital.audio or https://store.vital.audio from your own builds. This is against the terms of using those sites.
- Do not distribute the presets that come with the free version of Vital. They're under a separate license that does not allow redistribution.

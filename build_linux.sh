#!/bin/bash

# build_linux.sh - Build Vital synthesizer on Linux
# Usage: ./build_linux.sh [options]
#
# Options:
#   --config=Debug|Release   Build configuration (default: Debug)
#   --skip-regenerate        Skip Makefile regeneration (faster builds)
#   --no-run                 Build only, don't launch the app
#   --clean                  Clean build before building
#   --help                   Show this help message

set -e  # Exit on error

# Default values
CONFIG="Debug"
REGENERATE=true
RUN_APP=true
CLEAN_BUILD=false

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
JUCER_FILE="$SCRIPT_DIR/standalone/vital.jucer"
MAKEFILE_DIR="$SCRIPT_DIR/standalone/builds/linux"
BUILD_DIR="$MAKEFILE_DIR/build"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

echo_status() { echo -e "${GREEN}[+]${NC} $1"; }
echo_warn() { echo -e "${YELLOW}[!]${NC} $1"; }
echo_error() { echo -e "${RED}[X]${NC} $1"; }
echo_info() { echo -e "${CYAN}[i]${NC} $1"; }

show_help() {
    head -n 12 "$0" | tail -n 10
    exit 0
}

# Parse arguments
for arg in "$@"; do
    case $arg in
        --config=*)
            CONFIG="${arg#*=}"
            ;;
        --skip-regenerate)
            REGENERATE=false
            ;;
        --no-run)
            RUN_APP=false
            ;;
        --clean)
            CLEAN_BUILD=true
            ;;
        --help|-h)
            show_help
            ;;
        Debug|Release)
            CONFIG="$arg"
            ;;
        *)
            echo_error "Unknown option: $arg"
            show_help
            ;;
    esac
done

# ==============================================================================
# Step 1: Verify dependencies
# ==============================================================================
echo ""
echo "========================================"
echo "Step 1: Verifying dependencies"
echo "========================================"

# Check for make
if command -v make &> /dev/null; then
    MAKE_VERSION=$(make --version | head -n1)
    echo_status "make found: $MAKE_VERSION"
else
    echo_error "make not found. Please install build-essential:"
    echo "    sudo apt install build-essential"
    exit 1
fi

# Check for g++
if command -v g++ &> /dev/null; then
    GCC_VERSION=$(g++ --version | head -n1)
    echo_status "g++ found: $GCC_VERSION"
else
    echo_error "g++ not found. Please install build-essential:"
    echo "    sudo apt install build-essential"
    exit 1
fi

# Check for pkg-config
if command -v pkg-config &> /dev/null; then
    echo_status "pkg-config found"
else
    echo_error "pkg-config not found. Please install it:"
    echo "    sudo apt install pkg-config"
    exit 1
fi

# Check required libraries via pkg-config
REQUIRED_LIBS="alsa freetype2 libcurl jack"
MISSING_LIBS=""

for lib in $REQUIRED_LIBS; do
    if pkg-config --exists "$lib" 2>/dev/null; then
        echo_status "Found library: $lib"
    else
        MISSING_LIBS="$MISSING_LIBS $lib"
    fi
done

# Check for additional libraries that might not be in pkg-config
# libsecret and glib
if pkg-config --exists "libsecret-1" 2>/dev/null; then
    echo_status "Found library: libsecret-1"
else
    MISSING_LIBS="$MISSING_LIBS libsecret-1"
fi

if pkg-config --exists "glib-2.0" 2>/dev/null; then
    echo_status "Found library: glib-2.0"
else
    MISSING_LIBS="$MISSING_LIBS glib-2.0"
fi

# Check for OpenGL
if pkg-config --exists "gl" 2>/dev/null || [ -f /usr/lib/libGL.so ] || [ -f /usr/lib/x86_64-linux-gnu/libGL.so ] || [ -f /usr/lib/aarch64-linux-gnu/libGL.so ]; then
    echo_status "Found library: OpenGL"
else
    MISSING_LIBS="$MISSING_LIBS libgl"
fi

# Check for FFTW (optional but used by JUCE DSP)
if pkg-config --exists "fftw3f" 2>/dev/null; then
    echo_status "Found library: fftw3f"
else
    echo_warn "fftw3f not found (optional, but may be needed)"
fi

if [ -n "$MISSING_LIBS" ]; then
    echo_error "Missing required libraries:$MISSING_LIBS"
    echo ""
    echo "Install on Debian/Ubuntu with:"
    echo "    sudo apt install libasound2-dev libfreetype6-dev libcurl4-openssl-dev \\"
    echo "                     libsecret-1-dev libglib2.0-dev libgl1-mesa-dev \\"
    echo "                     libfftw3-dev libx11-dev libxrandr-dev libxinerama-dev \\"
    echo "                     libxcursor-dev libjack-jackd2-dev"
    echo ""
    echo "Install on Fedora/RHEL with:"
    echo "    sudo dnf install alsa-lib-devel freetype-devel libcurl-devel \\"
    echo "                     libsecret-devel glib2-devel mesa-libGL-devel \\"
    echo "                     fftw-devel libX11-devel libXrandr-devel libXinerama-devel \\"
    echo "                     libXcursor-devel jack-audio-connection-kit-devel"
    exit 1
fi

# Check for Projucer (required unless --skip-regenerate)
if [ "$REGENERATE" = true ]; then
    PROJUCER_PATHS=(
        "/usr/bin/Projucer"
        "/usr/local/bin/Projucer"
        "$HOME/JUCE/Projucer"
        "/opt/JUCE/Projucer"
        "$HOME/Applications/JUCE/Projucer"
    )

    PROJUCER_BIN=""
    for path in "${PROJUCER_PATHS[@]}"; do
        if [ -x "$path" ]; then
            PROJUCER_BIN="$path"
            break
        fi
    done

    if [ -z "$PROJUCER_BIN" ] && command -v Projucer &> /dev/null; then
        PROJUCER_BIN="Projucer"
    fi

    if [ -n "$PROJUCER_BIN" ]; then
        echo_status "Projucer found: $PROJUCER_BIN"
    else
        echo_error "Projucer not found. Install from: https://juce.com/get-juce/"
        echo "       Or use --skip-regenerate to skip Makefile regeneration"
        exit 1
    fi
fi

# Verify Makefile exists (only if skipping regeneration)
if [ "$REGENERATE" = false ]; then
    if [ -f "$MAKEFILE_DIR/Makefile" ]; then
        echo_status "Found Makefile: $MAKEFILE_DIR/Makefile"
    else
        echo_error "Makefile not found. Run without --skip-regenerate to create it."
        exit 1
    fi
fi

# ==============================================================================
# Step 2: Regenerate Makefile (optional)
# ==============================================================================
if [ "$REGENERATE" = true ]; then
    echo ""
    echo "========================================"
    echo "Step 2: Regenerating Makefile"
    echo "========================================"

    echo "Running: $PROJUCER_BIN --resave \"$JUCER_FILE\""
    "$PROJUCER_BIN" --resave "$JUCER_FILE"

    if [ -f "$MAKEFILE_DIR/Makefile" ]; then
        echo_status "Makefile regenerated successfully"
    else
        echo_error "Failed to regenerate Makefile"
        exit 1
    fi
else
    echo ""
    echo_info "Skipping Makefile regeneration (--skip-regenerate)"
fi

# ==============================================================================
# Step 3: Build with make
# ==============================================================================
echo ""
echo "========================================"
echo "Step 3: Building with make ($CONFIG)"
echo "========================================"

cd "$MAKEFILE_DIR"

# Clean if requested
if [ "$CLEAN_BUILD" = true ]; then
    echo_info "Cleaning build..."
    make CONFIG="$CONFIG" clean >/dev/null 2>&1 || true
fi

# Determine number of parallel jobs
if [ -n "$MAKEFLAGS" ]; then
    # User has set MAKEFLAGS, respect it
    JOBS=""
else
    # Use number of CPU cores
    NPROC=$(nproc 2>/dev/null || echo 4)
    JOBS="-j$NPROC"
fi

echo "Building with make CONFIG=$CONFIG $JOBS..."
echo ""

# Run make
if make CONFIG="$CONFIG" $JOBS; then
    BUILD_SUCCESS=true
else
    BUILD_SUCCESS=false
fi

# Find the built executable
EXE_PATH="$BUILD_DIR/vial"

if [ "$BUILD_SUCCESS" = true ] && [ -x "$EXE_PATH" ]; then
    echo ""
    echo_status "Build successful: $EXE_PATH"

    # Copy resource files next to the executable
    RESOURCE_FILES=("SYSTEM_PROMPT.md" "PRESET_SCHEMA.md")
    RESOURCE_SRC_DIR="$SCRIPT_DIR/agents/vital-assistant"

    for FILE in "${RESOURCE_FILES[@]}"; do
        if [ -f "$RESOURCE_SRC_DIR/$FILE" ]; then
            cp "$RESOURCE_SRC_DIR/$FILE" "$BUILD_DIR/$FILE"
            echo_status "Copied $FILE to $BUILD_DIR"
        else
            echo_warn "$FILE not found at $RESOURCE_SRC_DIR/$FILE"
        fi
    done
else
    echo_error "Build failed or could not find vial executable"
    exit 1
fi

# ==============================================================================
# Step 4: Run the app (optional)
# ==============================================================================
if [ "$RUN_APP" = true ]; then
    echo ""
    echo "========================================"
    echo "Step 4: Launching Vial"
    echo "========================================"

    # On ARM (e.g., Raspberry Pi), use software rendering for OpenGL compatibility
    if [ "$(uname -m)" = "aarch64" ] || [ "$(uname -m)" = "armv7l" ]; then
        echo_info "ARM detected - using software OpenGL rendering"
        export LIBGL_ALWAYS_SOFTWARE=1
    fi

    echo "Running: $EXE_PATH"
    "$EXE_PATH" &
    echo_status "Done! (running in background)"
else
    echo ""
    echo_status "Build complete (--no-run specified)"
    echo "App location: $EXE_PATH"
fi

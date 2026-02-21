#!/bin/bash

# build.sh - Cross-platform build script for Vital synthesizer
# Detects the current platform and runs the appropriate build script.
# All arguments are passed through to the platform-specific script.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Detect platform
case "$(uname -s)" in
    Darwin)
        PLATFORM="macos"
        BUILD_SCRIPT="$SCRIPT_DIR/build_macos.sh"
        ;;
    Linux)
        # Check if running in WSL
        if grep -qi microsoft /proc/version 2>/dev/null; then
            PLATFORM="windows"
            BUILD_SCRIPT="$SCRIPT_DIR/build_windows.bat"
        else
            PLATFORM="linux"
            BUILD_SCRIPT="$SCRIPT_DIR/build_linux.sh"
        fi
        ;;
    MINGW*|MSYS*|CYGWIN*)
        PLATFORM="windows"
        BUILD_SCRIPT="$SCRIPT_DIR/build_windows.bat"
        ;;
    *)
        echo "Unsupported platform: $(uname -s)"
        exit 1
        ;;
esac

echo "Detected platform: $PLATFORM"

# Check if build script exists
if [ ! -f "$BUILD_SCRIPT" ]; then
    echo "Build script not found: $BUILD_SCRIPT"
    exit 1
fi

# Run the appropriate build script
if [ "$PLATFORM" = "windows" ]; then
    # For Windows, run the batch file via cmd
    # Convert script path to Windows format
    if grep -qi microsoft /proc/version 2>/dev/null; then
        # WSL
        WIN_SCRIPT=$(wslpath -w "$BUILD_SCRIPT")
    else
        # Git Bash / MSYS / Cygwin - convert /c/path to C:\path
        WIN_SCRIPT=$(echo "$BUILD_SCRIPT" | sed 's|^/\([a-zA-Z]\)/|\1:\\|' | sed 's|/|\\|g')
    fi

    # Build the command with all arguments
    # We need to pass args carefully to avoid issues with = signs
    ARGS=""
    for arg in "$@"; do
        ARGS="$ARGS $arg"
    done

    cmd //c "$WIN_SCRIPT" $ARGS
else
    # macOS or Linux - run bash script directly
    "$BUILD_SCRIPT" "$@"
fi

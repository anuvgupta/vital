#!/bin/bash

# build_macos.sh - Build Vital synthesizer on macOS
# Usage: ./build_macos.sh [Debug|Release]

set -e  # Exit on error

CONFIG="${1:-Release}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
JUCER_FILE="$SCRIPT_DIR/standalone/vital.jucer"
XCODE_PROJECT="$SCRIPT_DIR/standalone/builds/osx/Vial.xcodeproj"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo_status() { echo -e "${GREEN}[✓]${NC} $1"; }
echo_warn() { echo -e "${YELLOW}[!]${NC} $1"; }
echo_error() { echo -e "${RED}[✗]${NC} $1"; }

# ==============================================================================
# Step 1: Verify dependencies
# ==============================================================================
echo ""
echo "========================================"
echo "Step 1: Verifying dependencies"
echo "========================================"

# Check for xcodebuild
if command -v xcodebuild &> /dev/null; then
    XCODE_VERSION=$(xcodebuild -version | head -n1)
    echo_status "xcodebuild found: $XCODE_VERSION"
else
    echo_error "xcodebuild not found. Please install Xcode command line tools:"
    echo "    xcode-select --install"
    exit 1
fi

# Check for Projucer - try common locations
PROJUCER_PATHS=(
    "/Applications/JUCE/Projucer.app/Contents/MacOS/Projucer"
    "/Applications/Projucer.app/Contents/MacOS/Projucer"
    "$HOME/JUCE/Projucer.app/Contents/MacOS/Projucer"
    "$HOME/Applications/JUCE/Projucer.app/Contents/MacOS/Projucer"
)

PROJUCER_BIN=""
for path in "${PROJUCER_PATHS[@]}"; do
    if [ -x "$path" ]; then
        PROJUCER_BIN="$path"
        break
    fi
done

# Also check if it's in PATH
if [ -z "$PROJUCER_BIN" ] && command -v Projucer &> /dev/null; then
    PROJUCER_BIN="Projucer"
fi

if [ -n "$PROJUCER_BIN" ]; then
    echo_status "Projucer found: $PROJUCER_BIN"
else
    echo_error "Projucer not found. Please install JUCE and ensure Projucer is in one of:"
    for path in "${PROJUCER_PATHS[@]}"; do
        echo "    - $path"
    done
    echo ""
    echo "Download JUCE from: https://juce.com/get-juce/"
    exit 1
fi

# Verify jucer file exists
if [ -f "$JUCER_FILE" ]; then
    echo_status "Found .jucer file: $JUCER_FILE"
else
    echo_error "Could not find .jucer file at: $JUCER_FILE"
    exit 1
fi

# ==============================================================================
# Step 2: Regenerate Xcode project with Projucer
# ==============================================================================
echo ""
echo "========================================"
echo "Step 2: Regenerating Xcode project"
echo "========================================"

echo "Running: $PROJUCER_BIN --resave \"$JUCER_FILE\""
"$PROJUCER_BIN" --resave "$JUCER_FILE"

if [ -d "$XCODE_PROJECT" ]; then
    echo_status "Xcode project regenerated successfully"
else
    echo_error "Failed to regenerate Xcode project"
    exit 1
fi

# ==============================================================================
# Step 3: Build with xcodebuild
# ==============================================================================
echo ""
echo "========================================"
echo "Step 3: Building with xcodebuild ($CONFIG)"
echo "========================================"

cd "$SCRIPT_DIR/standalone/builds/osx"

# Get available schemes
SCHEME=$(xcodebuild -project Vial.xcodeproj -list 2>/dev/null | grep -A 100 "Schemes:" | tail -n +2 | head -n 1 | xargs)

if [ -z "$SCHEME" ]; then
    SCHEME="Vial - App"  # Default scheme name for JUCE standalone apps
fi

echo "Using scheme: $SCHEME"
echo "Building..."

xcodebuild \
    -project Vial.xcodeproj \
    -scheme "$SCHEME" \
    -configuration "$CONFIG" \
    CODE_SIGN_IDENTITY="" \
    CODE_SIGNING_REQUIRED=NO \
    CODE_SIGNING_ALLOWED=NO \
    build \
    2>&1 | while read line; do
        # Show condensed output
        if [[ "$line" == *"error:"* ]]; then
            echo_error "$line"
        elif [[ "$line" == *"warning:"* ]]; then
            echo_warn "$line"
        elif [[ "$line" == *"BUILD SUCCEEDED"* ]]; then
            echo_status "$line"
        elif [[ "$line" == *"BUILD FAILED"* ]]; then
            echo_error "$line"
        elif [[ "$line" == *"Compiling"* ]] || [[ "$line" == *"Linking"* ]]; then
            echo "  $line"
        fi
    done

# Check if build succeeded by looking for the app
BUILD_DIR="$SCRIPT_DIR/standalone/builds/osx/build/$CONFIG"
APP_PATH="$BUILD_DIR/Vial.app"

# Also check DerivedData location
if [ ! -d "$APP_PATH" ]; then
    # Try to find in DerivedData
    DERIVED_DATA_APP=$(find ~/Library/Developer/Xcode/DerivedData -name "Vial.app" -path "*$CONFIG*" 2>/dev/null | head -n 1)
    if [ -n "$DERIVED_DATA_APP" ]; then
        APP_PATH="$DERIVED_DATA_APP"
    fi
fi

if [ -d "$APP_PATH" ]; then
    echo_status "Build successful: $APP_PATH"
else
    echo_error "Build may have failed - could not find Vial.app"
    echo "Check xcodebuild output above for errors"
    exit 1
fi

# ==============================================================================
# Step 4: Run the app
# ==============================================================================
echo ""
echo "========================================"
echo "Step 4: Launching Vial"
echo "========================================"

echo "Opening: $APP_PATH"
open "$APP_PATH"

echo_status "Done!"

# Fix Windows Voice Chat Crash: Add mbedTLS + initNetSystem

## Context

Clicking "Voice Chat" on Windows crashes the app. Root cause: the Windows build defines `IXWEBSOCKET_USE_SECURE_TRANSPORT=1` (Apple-only TLS backend). When ixwebsocket tries to create a TLS socket for the `wss://` Deepgram WebSocket, no TLS implementation matches on Windows, leaving a null socket pointer that gets dereferenced → crash. Secondary issue: `ix::initNetSystem()` (WSAStartup) is never called, which is required on Windows before socket operations.

## Plan

### Step 1: Download mbedTLS and add to `third_party/mbedtls/`

- Download mbedTLS 3.6.x release source from GitHub
- Place under `third_party/mbedtls/` with at minimum:
  - `include/` directory (headers)
  - `library/` directory (C source files)
- Add a `mbedtls_config.h` configuration if needed (or use default)

### Step 2: Update `standalone/builds/vs19/Vial_App.vcxproj`

**Preprocessor definitions** (lines 75, 90, 124, 139):
- Change `IXWEBSOCKET_USE_SECURE_TRANSPORT=1` → `IXWEBSOCKET_USE_MBED_TLS=1`
- Keep `IXWEBSOCKET_USE_TLS=1` as-is

**Include paths** (lines 74, 89, 123, 138):
- Add `../../../third_party/mbedtls/include` to AdditionalIncludeDirectories

**Source files** (after line 253 where IXSocketMbedTLS.cpp already is):
- Add all `*.c` files from `third_party/mbedtls/library/` as ClCompile items

**Linker** (lines 101, 153):
- Add `crypt32.lib` to AdditionalDependencies (needed by IXSocketMbedTLS.cpp for Windows certificate store access via wincrypt.h)

### Step 3: Add `ix::initNetSystem()` call in DeepgramClient

**File:** `src/common/deepgram_client.cpp`

- Add `#include "../../third_party/ixwebsocket/IXNetSystem.h"` at top
- Call `ix::initNetSystem()` at the start of `DeepgramClient::initialize()` (line 53)
- Call `ix::uninitNetSystem()` in `DeepgramClient::~DeepgramClient()` (line 44)

This is the simplest approach - DeepgramClient is the only ixwebsocket consumer, and `initNetSystem()` is a no-op on non-Windows.

### Step 4: Keep macOS/Linux unchanged

- macOS continues using `IXWEBSOCKET_USE_SECURE_TRANSPORT` (SecureTransport) - works fine
- Linux continues with its existing config
- Only the Windows vs19 build needs changes

## Files to modify

- `standalone/builds/vs19/Vial_App.vcxproj` - preprocessor defs, include paths, source files, linker libs
- `src/common/deepgram_client.cpp` - add initNetSystem/uninitNetSystem calls

## Files to create

- `third_party/mbedtls/` - mbedTLS source tree (downloaded from GitHub release)

## Verification

1. Open solution in Visual Studio 2019, build Debug/Release
2. Launch app on Windows, click Voice Chat
3. Should connect to Deepgram WebSocket via TLS without crash
4. Verify macOS/Linux builds still work (no changes to those build configs)

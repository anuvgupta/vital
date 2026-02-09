# Documenter Agent's Short-Term Memory

## Latest Task: Fix Windows Voice Chat TLS Crash (2026-02-09)

- Fixed Windows Voice Chat crash: null TLS socket in ixwebsocket
- Root cause: IXWEBSOCKET_USE_SECURE_TRANSPORT=1 is Apple-only; no TLS backend matched on Windows
- Integrated mbedTLS 3.6.5 as Windows TLS backend (third_party/mbedtls/)
- Added ix::initNetSystem()/ix::uninitNetSystem() to DeepgramClient
- Used forward declarations to avoid unity build header pollution from IXNetSystem.h
- Files touched: standalone/vital.jucer, src/common/deepgram_client.cpp, third_party/mbedtls/, standalone/builds/vs19/Vial_App.vcxproj
- Updated: STEERING.md, CHANGELOG.md, TROUBLESHOOTING.md, TODO.md

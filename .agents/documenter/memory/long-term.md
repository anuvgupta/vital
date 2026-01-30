# Documenter Agent's Long-Term Memory

## Architectural Patterns in Vital

### UI Listener Pattern
- UI sections (like VitalSidePanel) define inner `Listener` classes with pure virtual callbacks
- Parent components (like FullInterface) inherit from these Listeners and implement callbacks
- Registration via `addListener(this)` in parent's constructor
- This decouples UI components from business logic (API calls, preset manipulation, etc.)

### API Client Pattern
- ClaudeApiClient uses singleton pattern via `instance()` static method
- Initialization separate from construction (call `initialize()` after settings are loaded)
- HTTP requests run on background thread, callbacks delivered to UI thread via MessageManager

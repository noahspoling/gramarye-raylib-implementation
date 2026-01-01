# gramarye-raylib-implementation

Raylib implementation of the gramarye-renderer-interface. Provides a concrete implementation of the abstract renderer, input provider, and camera interfaces using raylib.

## Overview

gramarye-raylib-implementation bridges raylib's rendering API with the abstract renderer interface defined in gramarye-renderer-interface. This keeps all raylib-specific code isolated to this library, allowing the rest of the codebase to work with the abstract interface.

## Features

- **Renderer Implementation**: Implements Renderer interface using raylib
- **Input Provider Implementation**: Implements InputProvider interface using raylib input functions
- **Camera Support**: Implements camera transformations using raylib's Camera2D
- **Window Management**: Handles window creation, configuration, and lifecycle
- **Render Commands**: Converts abstract render commands to raylib draw calls

## Architecture

### Renderer Implementation

The `RendererRaylib` structure implements the Renderer interface:

- **Window Management**: Creates and manages raylib window with configurable flags
- **Frame Management**: Handles BeginDrawing/EndDrawing
- **Render Commands**: Converts RenderCommand structures to raylib draw calls:
  - `RENDER_COMMAND_TYPE_RECTANGLE` → `DrawRectangle`
  - `RENDER_COMMAND_TYPE_RECTANGLE_LINES` → `DrawRectangleLines`
  - `RENDER_COMMAND_TYPE_TEXTURE` → `DrawTexturePro`
  - `RENDER_COMMAND_TYPE_TEXTURE_PRO` → `DrawTexturePro`
  - `RENDER_COMMAND_TYPE_TEXT` → `DrawText`
  - `RENDER_COMMAND_TYPE_CLEAR` → `ClearBackground`

### Input Provider Implementation

The `InputProviderRaylib` structure implements the InputProvider interface:

- **Key Input**: Maps abstract key codes to raylib key codes
- **Mouse Input**: Provides mouse position and button states
- **Mouse Wheel**: Provides mouse wheel delta

### Camera Implementation

Camera transformations use raylib's Camera2D:

- **World to Screen**: Converts world coordinates to screen coordinates using camera transform
- **Screen to World**: Converts screen coordinates to world coordinates (inverse transform)
- **Zoom Support**: Handles camera zoom for coordinate transformations
- **Aspect Fit**: Supports aspect ratio fitting for different screen sizes

### Window Flags

Converts abstract WindowFlags to raylib config flags:

- `WINDOW_FLAG_VSYNC` → `FLAG_VSYNC_HINT`
- `WINDOW_FLAG_RESIZABLE` → `FLAG_WINDOW_RESIZABLE`
- `WINDOW_FLAG_BORDERLESS` → `FLAG_BORDERLESS_WINDOWED_MODE`
- `WINDOW_FLAG_MSAA_4X` → `FLAG_MSAA_4X_HINT`

**Important**: `SetConfigFlags()` must be called BEFORE `InitWindow()`.

## Usage

### Creating Renderer

```c
#include "renderer_raylib.h"

Renderer* renderer = RendererRaylib_create();
Renderer_init(renderer, 800, 600, "Game", WINDOW_FLAG_VSYNC);
```

### Creating Input Provider

```c
#include "input_raylib.h"

InputProvider* input = InputProviderRaylib_create();
```

### Render Loop

```c
Renderer_begin_frame(renderer);

// Create render commands
RenderCommand cmd = {
    .type = RENDER_COMMAND_TYPE_RECTANGLE,
    .bounds = {100, 100, 50, 50},
    .color = {255, 0, 0, 255}
};
Renderer_execute_command(renderer, &cmd);

Renderer_end_frame(renderer);
```

### Camera Transformations

```c
CameraHandle camera = &camera2D;
AspectFitHandle aspectFit = &fit;

// World to screen
RenderVector2 worldPos = {100.0f, 200.0f};
RenderVector2 screenPos = Renderer_world_to_screen(renderer, camera, aspectFit, worldPos);

// Screen to world
RenderVector2 mousePos = {400.0f, 300.0f};
RenderVector2 world = Renderer_screen_to_world(renderer, camera, aspectFit, mousePos);
```

## Dependencies

- **gramarye-renderer-interface**: Implements the abstract interfaces
- **raylib**: Rendering backend (version 5.5 or compatible)
- **gramarye-libcore**: For memory management (if needed)

## Building

This library is typically built as part of the main game project via CMake FetchContent or as a subdirectory. The parent project must provide raylib.

## Integration

This library is designed to be used as a submodule in game projects. It provides the concrete raylib implementation that games can use, while other systems work with the abstract interface.

## Raylib Version

This implementation is designed for raylib 5.5. Ensure your project uses a compatible version.

## Notes

- All raylib-specific code is isolated to this library
- Other systems (like gramarye-chunk-renderer) work with the abstract interface
- This allows switching rendering backends by providing a different implementation
- Window configuration flags must be set before window initialization


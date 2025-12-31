#ifndef CLAY_RENDERER_RAYLIB_H
#define CLAY_RENDERER_RAYLIB_H

#include "raylib.h"
#include "clay.h"

// This header provides declarations for the Clay ↔ Raylib renderer integration.
// The implementation is in src/clay_renderer_raylib.c

extern Camera Raylib_camera;

Ray GetScreenToWorldPointWithZDistance(Vector2 position, Camera camera, int screenWidth, int screenHeight, float zDistance);

void Clay_Raylib_Initialize(int width, int height, const char *title, unsigned int flags);
void Clay_Raylib_Close(void);
void Clay_Raylib_Render(Clay_RenderCommandArray renderCommands, Font* fonts);

#endif // CLAY_RENDERER_RAYLIB_H


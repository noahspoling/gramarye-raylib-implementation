#ifndef RENDERER_RAYLIB_H
#define RENDERER_RAYLIB_H

#include "renderer/renderer.h"

Renderer* RendererRaylib_create(void);
void RendererRaylib_destroy(Renderer* r);

#endif
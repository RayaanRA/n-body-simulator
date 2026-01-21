#ifdef USE_RAYLIB
#ifndef RENDER_RAYLIB_H
#define RENDER_RAYLIB_H

#include "cphys.h"
#include <raylib.h>

void render_init();
void render_draw(phys_system* system, double dt);
void render_close();

#endif
#endif
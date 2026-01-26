#ifdef USE_RAYLIB

#include "cphys.h"
#include <raylib.h>

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 900
#define SCALE 100.0
#define PHYSICS_STEPS 10

void render_init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "N-Body Simulation");
    SetTargetFPS(60);
}

void render_draw(phys_system* system, double dt) {
	BeginDrawing();
	DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0,0,0,15});

	for (int i = 0; i < system->count; i++) {
    	int x = SCREEN_WIDTH / 2 + system->bodies[i].pos.x * SCALE;
    	int y = SCREEN_HEIGHT / 2 - system->bodies[i].pos.y * SCALE;
    	DrawCircle(x, y, 10, WHITE);
	}

	EndDrawing();

	}

void render_close() {
    CloseWindow();
}

#endif

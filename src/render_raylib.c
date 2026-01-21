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
    for (int step = 0; step < PHYSICS_STEPS; step++) {
        integrate_step_system(system, LEAPFROG, dt);
        grav_force_system(system);
        accel_system(system);
    }

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

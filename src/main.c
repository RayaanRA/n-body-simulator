#include "cphys.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef USE_RAYLIB
#include "render_raylib.h"
#endif

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s <config_file> <dt> <steps>\n", argv[0]);
        return 1;
    }

    char* init_file_name = argv[1];
    double dt = atof(argv[2]);
    int steps = atoi(argv[3]);

    FILE *file = fopen(init_file_name, "r");
    if (!file) return 1;

    int N;
    double G, softening;
    fscanf(file, "N %d\n", &N);
    fscanf(file, "G %lf\n", &G);
    fscanf(file, "softening %lf\n", &softening);

    phys_body* bodies = malloc(sizeof(phys_body) * N);
    for (int i = 0; i < N; i++) {
        double x, y, vx, vy, m;
        fscanf(file, "%lf %lf %lf %lf %lf\n", &x, &y, &vx, &vy, &m);
        phys_init_body(&bodies[i], (phys_vector2){x, y}, (phys_vector2){vx, vy}, (phys_vector2){0,0}, m);
    }
    fclose(file);

    struct sim_ctx sim;
    sim_init(&sim, bodies, N, softening, G, dt, LEAPFROG);

#ifdef USE_RAYLIB
    render_init();
    while (!WindowShouldClose()) {
        render_draw(&sim.system, sim.dt);
    }
    render_close();
#else
    for (int i = 0; i < steps; i++)
        sim_step(&sim);
#endif

    free(bodies);
    return 0;
}

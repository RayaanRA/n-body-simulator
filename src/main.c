#include "cphys.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef USE_RAYLIB
#include "render_raylib.h"
#endif

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s <config_file> <dt> <steps> [csv_file]\n", argv[0]);
        return 1;
    }

    char* init_file_name = argv[1];
    double dt = atof(argv[2]);
    int steps = atoi(argv[3]);
    char* csv_file_name = (argc >= 5) ? argv[4] : NULL;

    FILE *csv_file = NULL;
    if (csv_file_name) {
        csv_file = fopen(csv_file_name, "a");
        if (!csv_file) {
            printf("Failed to open CSV file %s\n", csv_file_name);
            return 1;
        }
        // CSV header
        fprintf(csv_file, "step,energy,momentum_x,momentum_y");
    }

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

    if (csv_file) {
        for (int i = 0; i < N; i++) {
            fprintf(csv_file, ",body%d_pos_x,body%d_pos_y,body%d_vel_x,body%d_vel_y",
                    i, i, i, i);
        }
        fprintf(csv_file, "\n");
    }

    struct sim_ctx sim;
    sim_init(&sim, bodies, N, softening, G, dt, LEAPFROG);

    clock_t start_time = clock();

#ifdef USE_RAYLIB
    int step = 0;
    render_init();
    while (!WindowShouldClose()) {
        render_draw(&sim.system, sim.dt);

        if (csv_file) {
            phys_vector2 momentum = system_total_momentum(&sim.system);
            double energy = system_total_energy(&sim.system);

            fprintf(csv_file, "%d,%f,%f,%f", step, energy, momentum.x, momentum.y);
            for (int i = 0; i < N; i++) {
                fprintf(csv_file, ",%f,%f,%f,%f", sim.system.bodies[i].pos.x, sim.system.bodies[i].pos.y,
                        sim.system.bodies[i].vel.x, sim.system.bodies[i].vel.y);
            }
            fprintf(csv_file, "\n");
            step++;
        }
    }
    render_close();
#else
    for (int step = 0; step < steps; step++) {
        sim_step(&sim);

        if (csv_file) {
            phys_vector2 momentum = system_total_momentum(&sim.system);
            double energy = system_total_energy(&sim.system);

            fprintf(csv_file, "%d,%f,%f,%f", step, energy, momentum.x, momentum.y);
            for (int i = 0; i < N; i++) {
                fprintf(csv_file, ",%f,%f,%f,%f", sim.system.bodies[i].pos.x, sim.system.bodies[i].pos.y,
                        sim.system.bodies[i].vel.x, sim.system.bodies[i].vel.y);
            }
            fprintf(csv_file, "\n");
        }
    }
#endif

    if (csv_file) {
        clock_t end_time = clock();
        double runtime_sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        fprintf(csv_file, "# Simulation runtime (seconds): %f\n", runtime_sec);
        fclose(csv_file);
    }

    free(bodies);
    return 0;
}

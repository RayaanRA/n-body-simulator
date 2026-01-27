#include "cphys.h"
#include "sim.h"
#include "log.h"
#include "config.h"

#define PHYSICS_STEPS 10

#ifdef USE_RAYLIB
#include "render_raylib.h"
#endif

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s <config_file> <dt> <steps> [csv_file]\n", argv[0]);
        return 1;
    }

    char* config_file_name = argv[1];
    double dt = atof(argv[2]);
    int steps = atoi(argv[3]);

    int N;
    double G, softening;
    phys_body* bodies = init_bodies(config_file_name, &N, &G, &softening);
    if (!bodies) return 1;

    char* csv_file_name = (argc >= 5) ? argv[4] : NULL;
    FILE* csv_file = NULL;
    if (csv_file_name) {
        csv_file = init_csv(csv_file_name, N);       
    }

    struct sim_ctx sim;
    sim_init(&sim, bodies, N, softening, G, dt, LEAPFROG);

    clock_t start_time = clock();

#ifdef USE_RAYLIB
    int step = 0;
    render_init();
    while (!WindowShouldClose()) {
        for (int i = 0; i < PHYSICS_STEPS; i++) {
            integrate_step_system(&sim.system, LEAPFROG, dt);
            if (csv_file) {
                log_data(csv_file, step, &sim);                
            }
            step++;
        }
        render_draw(&sim.system, dt);

    }
    render_close();
#else
    for (int step = 0; step < steps; step++) {
        sim_step(&sim);

        if (csv_file) {
            log_data(csv_file, step, &sim);
        }
    }
#endif

    if (csv_file) {
        clock_t end_time = clock();
        log_time(csv_file, start_time, end_time);
        fclose(csv_file);
    }

    free(bodies);
    return 0;
}

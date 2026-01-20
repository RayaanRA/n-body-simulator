#include "cphys.h"

int main(int argc, char **argv) {
    phys_body *bodies = 0;
    phys_system system;

    int n = 0;
    double dt = 0.0;
    int steps = 0;

    // parse inputs (n, dt, steps, initial conditions)

    // allocate and initialize bodies

    phys_init_system(&system, bodies, n, 1.0, 0.0);

    grav_force_system(&system);
    accel_system(&system);

    for (int i = 0; i < steps; i++) {
        integrate_step_system(&system, LEAPFROG, dt);
        grav_force_system(&system);
        accel_system(&system);

        // log state / energy / positions
    }

    // cleanup

    return 0;
}

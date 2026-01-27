#include "config.h"

phys_body* init_bodies(char* config_file_name, int* N, double* G, double* softening) {
    FILE *file = fopen(config_file_name, "r");
    if (!file) return NULL;
    fscanf(file, "N %d\n", N);
    fscanf(file, "G %lf\n", G);
    fscanf(file, "softening %lf\n", softening);

    phys_body* bodies = malloc(sizeof(phys_body) * (*N));
    for (int i = 0; i < *N; i++) {
        double x, y, vx, vy, m;
        fscanf(file, "%lf %lf %lf %lf %lf\n", &x, &y, &vx, &vy, &m);
        phys_init_body(&bodies[i], (phys_vector2){x, y}, (phys_vector2){vx, vy}, (phys_vector2){0,0}, m);
    }
    fclose(file);
    return bodies;
}
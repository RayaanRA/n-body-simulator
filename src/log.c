#include "log.h"

FILE* init_csv(char* csv_file_name, int N) {
        FILE* csv_file = fopen(csv_file_name, "a");
        if (!csv_file) {
            printf("Failed to open CSV file %s\n", csv_file_name);
            return NULL;
        }
        // CSV header
        fprintf(csv_file, "step,energy,momentum_x,momentum_y");
        for (int i = 0; i < N; i++) {
        	fprintf(csv_file, ",body%d_pos_x,body%d_pos_y,body%d_vel_x,body%d_vel_y",
            	i, i, i, i);
        	}
        	fprintf(csv_file, "\n");

    return csv_file;
}

void log_data(FILE* csv_file, int step, struct sim_ctx* sim) {
	phys_vector2 momentum = system_total_momentum(&sim->system);
    double energy = system_total_energy(&sim->system);
    fprintf(csv_file, "%d,%f,%f,%f", step, energy, momentum.x, momentum.y);
    for (int i = 0; i < sim->system.count; i++) {
        fprintf(csv_file, ",%f,%f,%f,%f", sim->system.bodies[i].pos.x, sim->system.bodies[i].pos.y,
        sim->system.bodies[i].vel.x, sim->system.bodies[i].vel.y);
    }
    fprintf(csv_file, "\n");
}

void log_time(FILE* csv_file, clock_t start_time, clock_t end_time) {
	double runtime_sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    fprintf(csv_file, "# Simulation runtime (seconds): %f\n", runtime_sec);
}
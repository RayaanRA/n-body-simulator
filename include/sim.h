#ifndef SIM_H
#define SIM_H

#include "cphys.h"
#include <stdio.h>

struct sim_ctx {
	phys_system system;
	double dt;
	enum integrator integrator;
};

void sim_init(struct sim_ctx* ctx, phys_body* bodies, size_t N, double softening, double G, double dt, enum integrator integrator);
void sim_step(struct sim_ctx* ctx);

#endif
#include "sim.h"

void sim_init(struct sim_ctx* ctx, phys_body* bodies, size_t N, double softening, double G, double dt, enum integrator integrator) {
	phys_init_system(&ctx->system, bodies, N, softening, G);
	grav_force_system(&ctx->system);
	accel_system(&ctx->system);
	ctx->dt = dt;
	ctx->integrator = integrator;
}

void sim_step(struct sim_ctx* ctx) {
	integrate_step_system(&ctx->system, ctx->integrator, ctx->dt);
}
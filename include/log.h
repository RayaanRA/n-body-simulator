#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>
#include "cphys.h"
#include "sim.h"

FILE* init_csv(char* csv_file_name, int N);
void log_data(FILE* csv_file, int step, struct sim_ctx* sim);
void log_time(FILE* csv_file, clock_t start_time, clock_t end_time);

#endif
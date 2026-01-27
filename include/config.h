#ifndef CONFIG_H
#define CONFIG_H

#include "cphys.h"
#include <stdlib.h>
#include <stdio.h>

phys_body* init_bodies(char* config_file_name, int* N, double* G, double* softening);

#endif
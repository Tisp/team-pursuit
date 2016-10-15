#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#include "util.h"
#include "track.h"
#include "cyclist.h"
#include "teams.h"

void simulator_start(int track_distance, int num_cyclists);

void simulator_start_running(Teams *teams);

#endif
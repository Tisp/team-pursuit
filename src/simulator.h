#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "config.h"
#include "util.h"
#include "track.h"
#include "cyclist.h"
#include "teams.h"

void simulator_start(int track_distance, int num_cyclists, int speed_type);

void simulator_start_running(Teams *teams);

int simulator_break_cyclist(Teams *teams, int team_id);

void simulator_create_threads(Teams *teams);

int simulator_change_speed(Teams *teams, int team_id);

void simulator_update_positions(Teams *teams, int track_size);


#endif
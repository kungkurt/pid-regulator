#ifndef PID_OUTPUT_H_
#define PID_OUTPUT_H_

#include "config.h"

component
plant_t pid_output(ihc::stream_in<pid_struct>& din, plant_t output);

#endif
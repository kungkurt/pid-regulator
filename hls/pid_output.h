#ifndef PID_OUTPUT_H_
#define PID_OUTPUT_H_

#include "config.h"

hls_always_run_component component
plant_t pid_output(ihc::stream_in<pid_struct>& din);

#endif
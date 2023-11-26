#ifndef PID_OUTPUT_H_
#define PID_OUTPUT_H_

#include "config.h"

#define LOG_SIZE 20

hls_always_run_component component
pid_t pid_output(ihc::stream_in<pid_t>& pin,
                 ihc::stream_in<pid_t>& iin,
                 ihc::stream_in<pid_t>& din);

#endif
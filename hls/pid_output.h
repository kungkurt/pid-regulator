#ifndef PID_OUTPUT_H_
#define PID_OUTPUT_H_

#include "config.h"

#define LOG_SIZE 30

hls_always_run_component component
void pid_output(ihc::stream_in<pid_t>& pin,
                ihc::stream_in<pid_t>& iin,
                ihc::stream_in<pid_t>& din,
                hls_avalon_slave_memory_argument(LOG_SIZE*sizeof(short int)) short int* result);

#endif
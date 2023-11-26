#ifndef INTEGRAL_H_
#define INTEGRAL_H_

#include "config.h"

#define CLAMP_LOW_LIMIT  -70
#define CLAMP_HIGH_LIMIT 70

//hls_always_run_component
component
void integral(ihc::stream_in<i_struct>& din, ihc::stream_out<pid_t>& dout);

#endif
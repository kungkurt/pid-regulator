#ifndef DERIVATIVE_H_
#define DERIVATIVE_H_

#include "proportional.h"

hls_always_run_component component
void derivative(ihc::stream_in<pid_struct>& din, ihc::stream_out<pid_struct>& dout);

#endif
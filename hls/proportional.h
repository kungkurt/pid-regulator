#ifndef PROPORTIONAL_H_
#define PROPORTIONAL_H_

#include "HLS/hls.h"
#include "config.h"

hls_always_run_component component
void proportional(ihc::stream_in<p_struct>& din, ihc::stream_out<pid_t>& dout);

#endif
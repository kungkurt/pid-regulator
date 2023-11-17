#ifndef INTEGRAL_H_
#define INTEGRAL_H_

#include "config.h"

#define CLAMP_LOW_LIMIT  -511
#define CLAMP_HIGH_LIMIT 511

component
void integral(ihc::stream_in<pid_struct>& din, ihc::stream_out<pid_struct>& dout);

#endif
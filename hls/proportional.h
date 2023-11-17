#ifndef PROPORTIONAL_H_
#define PROPORTIONAL_H_

#include "config.h"

component
void proportional(ihc::stream_in<pid_struct>& din, ihc::stream_out<pid_struct>& dout);

#endif
#ifndef PID_INPUT_H_
#define PID_INPUT_H_

#include "config.h"

hls_avalon_slave_component component
void pid_input(hls_avalon_slave_memory_argument(NR_ARGS*sizeof(float)) float* settings,
               hls_avalon_slave_register_argument short setpoint,
               pid_t sensor_value,
               bool pid_reset,
               ihc::stream_out<p_struct>& pout,
               ihc::stream_out<i_struct>& iout,
               ihc::stream_out<d_struct>& dout);

#endif
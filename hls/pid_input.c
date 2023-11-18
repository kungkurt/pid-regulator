#include "pid_input.h"

hls_avalon_slave_component component
void pid_input(hls_avalon_slave_memory_argument(NR_ARGS*sizeof(float)) float* settings,
               hls_avalon_slave_register_argument short setpoint,
               pid_t sensor_value,
               bool reset,
               ihc::stream_out<p_struct>& pout,
               ihc::stream_out<i_struct>& iout,
               ihc::stream_out<d_struct>& dout) {
    pid_t sp = setpoint;
    pid_t error = sp - sensor_value;

    p_struct p = {
        reset,
        error,
        settings[1]
    };

    i_struct i = {
        reset,
        settings[0],
        error,
        settings[2]
    };

    d_struct d = {
        reset,
        settings[0],
        error,
        settings[3]
    };

    pout.write(p);
    iout.write(i);
    dout.write(d);
}
#include "pid_input.h"

hls_avalon_slave_component component
void pid_input(hls_avalon_slave_memory_argument(NR_ARGS*sizeof(float)) float* settings,
               hls_avalon_slave_register_argument short setpoint,
               sensor_t sensor_value,
               bool pid_reset,
               ihc::stream_out<p_struct>& pout,
               ihc::stream_out<i_struct>& iout,
               ihc::stream_out<d_struct>& dout) {
    static p_struct p;
    static i_struct i;
    static d_struct d;
    static pid_t old_sp = false;
    pid_t sp = setpoint;
    pid_t error;
    bool rst;

    if(sp != old_sp || pid_reset) {
        error = 0.0;
        rst = true;
    } else {
        error = sp - sensor_value;
        rst = false;
    }

    p.reset = rst;
    p.error = error;
    p.Gp = settings[1];

    i.reset = rst;
    i.freq = settings[0];
    i.error = error;
    i.Gi = settings[2];

    d.reset = rst;
    d.freq = settings[0];
    d.error = error;
    d.Gd = settings[3];

    old_sp = sp;

    pout.write(p);
    iout.write(i);
    dout.write(d);
}
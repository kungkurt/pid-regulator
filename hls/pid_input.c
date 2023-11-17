#include "pid_input.h"

hls_avalon_slave_component component
void pid_input(hls_avalon_slave_memory_argument(NR_ARGS*sizeof(float)) float* settings,
               hls_avalon_slave_register_argument short setpoint,
               pid_t sensor_value,
               bool reset,
               ihc::stream_out<pid_struct>& dout) {
    pid_t sp = setpoint, sv = sensor_value;
    pid_t error = sp - sv;

    static pid_struct work = {
        reset,
        error,
        settings[0],
        settings[1],
        settings[2],
        settings[3],
        0.0,
        0.0,
        0.0
    }

    dout.write(work);
}
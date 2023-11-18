#include "derivative.h"

hls_always_run_component component
void derivative(ihc::stream_in<d_struct>& din, ihc::stream_out<pid_t>& dout) {

    // declare variables
    static pid_t last_error = 0.0;
    pid_t ret = 0;
    d_struct work = din.read();

    ret = work.Gd * ((work.error - last_error) / work.freq);

    if(work.reset) {
        // reset is active
        ret = 0;
        last_error = 0;
    } else {
        // calculate derivative
        last_error = work.error;
    }

    // send output
    dout.write(ret);
}
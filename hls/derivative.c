#include "derivative.h"

hls_always_run_component component
void derivative(ihc::stream_in<d_struct>& din, ihc::stream_out<pid_t>& dout) {

    // declare variables
    static pid_t last_error = 0.0;
    d_struct work = din.read();
    pid_t ret;

    // calculate derivative
    if(work.reset) {
        ret = 0.0f;
    } else {
        ret = work.Gd * ((work.error - last_error) / work.freq);
    }

    // during reset work.error will be 0
    // no special logic is needed.
    last_error = work.error;
    
    // send output
    dout.write(ret);
}
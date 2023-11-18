#include "derivative.h"

hls_always_run_component component
void derivative(ihc::stream_in<pid_struct>& din, ihc::stream_out<pid_struct>& dout) {

    // register to hold last_error value
    static pid_t last_error = 0.0;

    // pid_struct to work on
    pid_struct work = din.read();

    // calculate derivative
    work.d = work.Gd * ((work.error - last_error) / work.freq);

    // if reset is active
    if(work.reset) {
        work.d = 0;
        last_error = 0;
    } else {
        last_error = work.error;
    }

    // send output
    dout.write(work);
}
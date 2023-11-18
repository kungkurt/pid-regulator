#include "proportional.h"

hls_always_run_component component
void proportional(ihc::stream_in<p_struct>& din, ihc::stream_out<pid_t>& dout) {

    // read data in to local register.
    p_struct work = din.read();
    pid_t ret = 0;

    // calculate proportional.
    if(work.reset) {
        ret = 0;
    } else {
        ret = work.Gp * work.error;
    }

    // write localregister to output.
    dout.write(ret);
}
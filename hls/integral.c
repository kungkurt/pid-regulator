#include "integral.h"

hls_always_run_component component
void integral(ihc::stream_in<i_struct>& din, ihc::stream_out<pid_t>& dout) {
    static pid_t reset_reg = 0.0;
    i_struct work = din.read();
    pid_t ret = 0;

    if(work.reset) {
        // reset register on active reset.
        reset_reg = 0;
    } else if(!(reset_reg > CLAMP_HIGH_LIMIT || reset_reg < CLAMP_LOW_LIMIT)) {
        // calculate output but do not accumulate during integral windup.
        reset_reg = reset_reg + ((work.Gi / work.freq) * work.error);
        ret = work.Gi + reset_reg;
    } else {
        // integral windup disable integral.
        ret = 0;
    }

    // write result on output.
    dout.write(ret);
}
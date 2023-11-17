#include "integral.h"

component
void integral(ihc::stream_in<pid_struct>& din, ihc::stream_out<pid_struct>& dout) {
    static reset_reg = 0.0;
    pid_struct work = din.read();

    // reset register if setpoint is reached.
    if(work->error == 0 || work->reset) {
        reset_reg = 0;
    }

    // calculate output but do not accumulate during integral windup.
    if(!(reset_reg > CLAMP_HIGH_LIMIT || reset_reg < CLAMP_LOW_LIMIT)) {
        reset_reg = reset_reg + ((work->Gi / work->freq) * work->error);
        work->Ki = Gi * error + reset_reg;
    } else {
        work->Ki = 0;
    }

    // write result on output.
    dout.write(work);
}
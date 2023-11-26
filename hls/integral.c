#include "integral.h"

//hls_always_run_component
component
void integral(ihc::stream_in<i_struct>& din, ihc::stream_out<pid_t>& dout) {
    static pid_t reset_reg = 0.0;
    i_struct work = din.read();
    pid_t ret = 0;

    if(work.reset) {
        // reset register on active reset.
        reset_reg = 0.0f;
    } else {
        reset_reg = reset_reg + ((work.Gi / work.freq) * work.error);
    }

    if(!(reset_reg > CLAMP_HIGH_LIMIT || reset_reg < CLAMP_LOW_LIMIT)) {
        // calculate output but do not accumulate during integral windup.
        // for now the limits for clamp are defined during compile time.
        // will add a thenth of the gain with for each clock period with a update frequency of 100ms
        // with a frequency of 500ms it will add a half of gain each clock period
        // and with a frequency of one second a whole gain will be added each clock period
        // this can need to be adjusted with diffrent sensor and plant. 
        // this is just an example.
        ret = (work.Gi * work.error) + reset_reg;
    } else {
        // integral windup disable integral.
        ret = 0;
    }

    // write result on output.
    dout.write(ret);
}
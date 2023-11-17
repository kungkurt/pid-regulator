#include "proportional.h"

component
void proportional(ihc::stream_in<pid_struct>& din, ihc::stream_out<pid_struct>& dout) {

    // read data in to local register.
    pid_struct work = din.read();

    // calculate proportional.
    if(work->reset) {
        work->p = 0;
    } else {
        work->p = work->Gp * work->error;
    }

    // write localregister to output.
    dout.write(work);
}
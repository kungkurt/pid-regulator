#include "pid_output.h"

hls_always_run_component component
pid_t pid_output(ihc::stream_in<pid_t>& pin,
                 ihc::stream_in<pid_t>& iin,
                 ihc::stream_in<pid_t>& din) {

    // declare variables.
    pid_t p = pin.read();
    pid_t i = iin.read();
    pid_t d = din.read();

    // calculate current result value.
    return p + i + d;
}
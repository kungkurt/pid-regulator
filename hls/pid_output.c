#include "pid_output.h"

hls_always_run_component component
plant_t pid_output(ihc::stream_in<pid_struct>& din) {
    pid_struct work = din.read();
    plant_t output = (work.p + work.i + work.d).to_ac_int();
    
    return output;
}
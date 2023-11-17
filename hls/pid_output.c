#include "pid_output.h"

component
plant_t pid_output(ihc::stream_in<pid_struct>& din, plant_t output) {
    pid_struct work = din.read();
    plant_t output = work->p + work->i work->d;
    
    return output;
}
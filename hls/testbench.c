#include <stdio.h>
#include "pid.h"

#define test_samples 405

pid_t sw_plant(pid_t x) {
    
}

int main(void) {
    float settings[NR_SETTINGS] = {
        0.1,                            // proportional gain
        10.0,                           // integral gain
        0.0,                            // derivative gain
        75.0,                           // min value
        1023.0,                         // max value
        0.01                            // update frequency (seconds)
    }
    bool reset = true;
    sp_t sp;
    sensor_t sv = 0;
    plant_t results[test_samples];

    for(int i = 0; i < test_samples; i++) {
        if(i < 5) {                     // setpoint 0
           sp = 0.0 
        } else if(i < 105) {            // setpoint 500
            sp = 500.0
        } else if(i < 205) {            // setpoint 250
            sp = 250.0
        } else if(i < 305) {            // setpoint 800
            sp = 800.0
        } else {                        // setpoint 0
            sp = 0.0
        }
        ihc_hls_enqueue(&results[i], &pid, settings, sp, sv, reset);
        if(reset) reset = false;
    }

    ihc_hls_component_run_all(pid);

    for(int i = 0; i < test_samples; i++) {
        printf("%i: %i\n", i, (int) results[i]);
    }
}
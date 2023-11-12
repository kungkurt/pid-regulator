#include <stdio.h>
#include "pid.h"

#define test_samples 405

int main(void) {
    float settings[NR_SETTINGS] = {
        1.0,                            // proportional gain
        0.5,                           // integral gain
        0.0,                            // derivative gain
        25.0,                           // min value
        1023.0,                         // max value
        0.01                            // update frequency (seconds)
    };
    bool reset = true;
    sp_t sp;
    sensor_t sv = 0;
    plant_t results[test_samples];

    for(int i = 0; i < test_samples; i++) {
        if(i < 5) {                     // setpoint 0
           sp = 0; 
        } else if(i < 105) {            // setpoint 50
            sp = 500;
        } else if(i < 205) {            // setpoint 25
            sp = 250;
        } else if(i < 305) {            // setpoint 80
            sp = 800;
        } else {                        // setpoint 0
            sp = 0;
        }
        if(reset) reset = false;
        sv = results[i];
    }

    for(int i = 0; i < test_samples; i++) {
        printf("%i: %i\n", i, (int) results[i]);
    }

    return 0;
}
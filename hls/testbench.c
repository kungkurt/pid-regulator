#include <stdio.h>
#include "pid.h"

#define test_samples 405

int main(void) {
    float *settings[NR_ARGS] = {
        0.1,                            // proportional gain
        0.0,                            // integral gain
        0.0,                            // derivative gain
        25.0,                           // min value
        1023.0,                         // max value
        0.01                            // update frequency (seconds)
    };
    bool reset = true;
    pid_t sp;
    pid_t sv = 0;
    pid_t *plant;
    pid_t results[test_samples];

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
        pid(settings, sp, plant, sv, reset);
        if(reset) reset = false;
        sv = &plant;
    }

    for(int i = 0; i < test_samples; i++) {
        printf("%i: %i\n", i, (int) results[i]);
    }

    return 0;
}
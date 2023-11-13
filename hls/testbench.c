#include <stdio.h>
#include "pid.h"

#define test_samples 405

int main(void) {
    bool reset = true;
    short int sp;
    pid_t sv = 0;
    plant_t results[test_samples];
    plant_t actuator = 0;
    plant_t *plant = &actuator;
    float settings[NR_ARGS] = {
        0.1f,                            // proportional gain
        0.0f,                            // integral gain
        0.0f,                            // derivative gain
        25.0f,                           // min value
        1023.0f,                         // max value
        0.01f                            // update frequency (seconds)
    };

    for(int i = 0; i < test_samples; i++) {
        if(i == 0) {                    // setpoint 0
            printf("setpoint: 0\n-----------\n");
            sp = 0;
            reset = true;
        } else if(i == 5) {             // setpoint 655
            printf("setpoint: 655\n-------------\n");
            sp = 655;
            reset = false;
        } else if(i == 100) {            // setpoint 500
            printf("setpoint: 500\n-------------\n");
            sp = 500;
        } else if(i == 200) {            // setpoint 250
            printf("setpoint: 250\n-------------\n");
            sp = 250;
        } else if(i == 300) {            // setpoint 800
            printf("setpoint: 800\n-------------\n");
            sp = 800;
        } else {                         // setpoint 0
            sp = 0;
        }
        pid(settings, sp, plant, sv, reset);
        if(reset) reset = false;
        results[i] = *plant;
    }

    for(int i = 0; i < test_samples; i++) {
        printf("%i: %i\n", i, (int)results[i]);
    }

    return 0;
}
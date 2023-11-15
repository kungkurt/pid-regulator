#include <stdlib.h>
#include <time.h>
#include "HLS/stdio.h"
#include "pid.h"

#define test_samples 105

int main(void) {
    double prandom;
    time_t t;
    int temp;

    bool reset = true;
    short sp;
    pid_t sv = 0;
    plant_t results[test_samples];
    float settings[NR_ARGS] = {
        0.3f,                            // proportional gain
        0.6f,                            // integral gain
        0.0f,                            // derivative gain
        -1023.0f,                        // min value
        1023.0f,                         // max value
        0.01f                            // update frequency (seconds)
    };

    // init pseudo rng.
    srand((unsigned) time(&t));

    for(int i = 0; i < test_samples; i++) {
        prandom = (double)rand() / (double)((unsigned)RAND_MAX+1);
        if(i == 0) {                    // setpoint 0
            printf("setpoint: 0\n-----------\n");
            sp = 0;
        } else if(i == 5) {             // setpoint 655
            printf("setpoint: 655\n-------------\n");
            sp = 655;
        } else if(i == 25) {            // setpoint 500
            printf("setpoint: 500\n-------------\n");
            sp = 500;
        } else if(i == 45) {            // setpoint 250
            printf("setpoint: 250\n-------------\n");
            sp = 250;
        } else if(i == 65) {            // setpoint 800
            printf("setpoint: 800\n-------------\n");
            sp = 800;
        } else if(i == 85){             // setpoint 0
            printf("setpoint: 0\n-----------\n");
            sp = 0;
        }
        results[i] = pid(settings, sp, sv, reset);

        // create simulated noice on signal.
        temp = results[i];
        sv = temp + prandom;

        // only use reset on first iteration.
        if(reset) reset = false;
    }

    for(int i = 0; i < test_samples; i++) {
        printf("%i: %i\n", i, (int)results[i]);
    }

    return 0;
}
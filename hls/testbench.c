#include <stdlib.h>
#include <time.h>
#include "HLS/stdio.h"
#include "pid.h"

#define test_samples 105

plant_t plant = 0;

void process_plant_value(plant_t value) {
    double v = value.to_double();
    if(value > 50) {
        v = v * 0.8;
        value = v;
    }
    plant = plant + (int)value;
}

int main(void) {
    double prandom;
    time_t t;
    plant_t temp;

    bool reset = true;
    short sp;
    pid_t sv = 0;
    plant_t results[test_samples];
    float settings[NR_ARGS] = {
        0.12f,                           // proportional gain
        0.68f,                           // integral gain
        1.1f,                            // derivative gain
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

        // run DUT
        temp = pid(settings, sp, sv, reset);

        // create simulated sensor signal.
        process_plant_value(temp);
        sv = plant;

        // only use reset on first iteration.
        if(reset) reset = false;

        // set result as current sensor value.
        results[i] = sv.to_ac_int();
    }

    for(int i = 0; i < test_samples; i++) {
        switch(i) {
            case 0:
            printf("reset..\n");
            break;
            case 1:
            printf("\nsetpoint 0\n");
            break;
            case 5:
            printf("\nsetpoint 655\n");
            break;
            case 25:
            printf("\nsetpoint 500\n");
            break;
            case 45:
            printf("\nsetpoint 250\n");
            break;
            case 65:
            printf("\nsetpoint 800\n");
            break;
            case 85:
            printf("\nsetpoint 0\n");
            break;
            default:
            if(i % 5 == 0) printf("\n")
        }
        printf("\t%i", i, (int)results[i]);
    }

    return 0;
}
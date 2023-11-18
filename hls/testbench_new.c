#include "HLS/stdio.h"
#include <stdio.h>
#include "pid_input.h"
#include "proportional.h"
#include "integral.h"
#include "derivative.h"
#include "pid_output.h"
#include "config.h"

#define test_samples 105

plant_t plant = 0;
sensor_t sensor = 0;

void process_plant_value(plant_t value) {
    double v = value.to_double();

    // make sure big changes take longer to reach.
    if(value > 5 || value < -5) {
        v = v * 0.8;
        value = v;
    }

    plant = plant + value;
    sensor = plant;
}

int main(void) {
    bool reset = true;
    short sp;
    sensor_t sv = 0;
    pid_struct results_input[test_samples];
    pid_struct results_p[test_samples];
    pid_struct results_i[test_samples];
    pid_struct results_d[test_samples];
    plant_t results[test_samples];
    plant_t results_plant[test_samples];
    float settings[NR_ARGS] = {
        0.10f,                            // update frequency (seconds)
        0.701f,                           // proportional gain
        0.050f,                           // integral gain
        0.041f                            // derivative gain
    };

    // Streams
    ihc::stream_out<pid_struct> pid_input_out;
    ihc::stream_in<pid_struct>  proportion_in;
    ihc::stream_out<pid_struct> proportion_out;
    ihc::stream_in<pid_struct>  integral_in;
    ihc::stream_out<pid_struct> integral_out;
    ihc::stream_in<pid_struct>  derivative_in;
    ihc::stream_out<pid_struct> derivative_out;
    ihc::stream_in<pid_struct>  pid_output_in;

    // . . . . . . . . . . . . . .
    // . . pid input testbench . .
    // . . . . . . . . . . . . . .
    for(int i = 0; i < test_samples; i++) {
        if(i == 0) {                    // setpoint 0
            printf("setpoint: 0\n-----------\n");
            sp = 0;
        } else if(i == 5) {             // setpoint 655
            printf("setpoint: 69\n-------------\n");
            sp = 69;
        } else if(i == 25) {            // setpoint 500
            printf("setpoint: 50\n-------------\n");
            sp = 50;
        } else if(i == 45) {            // setpoint 250
            printf("setpoint: 25\n-------------\n");
            sp = 25;
        } else if(i == 65) {            // setpoint 800
            printf("setpoint: 95\n-------------\n");
            sp = 95;
        } else if(i == 85){             // setpoint 0
            printf("setpoint: 0\n-----------\n");
            sp = 0;
        }

        // run DUT
        pid_input(settings, sp, sv, reset, pid_input_out);

        // read output
        results_input[i] = pid_input_out.read();

        // . . . . . . . . . . . . . . . .
        // . . proportional  testbench . .
        // . . . . . . . . . . . . . . . .
        proportion_in.write(results_input[i]);                                      // populate proportional stream

        // run proportional
        ihc_hls_enqueue_noret(&proportional, proportion_in, proportion_out);        // que proportional invocations
        ihc_hls_component_run_all(proportional);                                    // run proportional invocations

        results_p[i] = proportion_out.read();                                       // read proportional output

        // . . . . . . . . . . . . . .
        // . . integral  testbench . .
        // . . . . . . . . . . . . . .
        integral_in.write(results_p[i]);                                        // populate integral stream

        // run integral
        ihc_hls_enqueue_noret(&integral, integral_in, integral_out);                // que integral invocations
        ihc_hls_component_run_all(integral);                                        // run integral invocations

        results_i[i] = integral_out.read();                                         // read integral output

        // . . . . . . . . . . . . . . .
        // . . derivative  testbench . .
        // . . . . . . . . . . . . . . .
        derivative_in.write(results_i[i]);                                      // populate derivative stream

        // run integral
        ihc_hls_enqueue_noret(&derivative, derivative_in, derivative_out);          // que derivative invocations
        ihc_hls_component_run_all(derivative);                                      // run derivative invocations

        results_d[i] = derivative_out.read();                                       // read derivative output

        // . . . . . . . . . . . . . . .
        // . . pid output  testbench . .
        // . . . . . . . . . . . . . . .
        pid_output_in.write(results_d[i]);
        ihc_hls_enqueue(&results[i], &pid_output, pid_output_in);
        ihc_hls_component_run_all(pid_output);

        // TODO simulate sensor value(sv) and do some process value conversion between plant and sensor.
        // this should also be implemented in HW.... when some sensor and actuator is known....
        process_plant_value(results[i]);
        sv = sensor;
        results_plant[i] = plant;

        printf("plant = %d\nsensor = %d\n", plant.to_int(), (int)sensor);

        if(reset) reset = false;
    }

    // . . . . . . . . . . . . . . . .
    // . . output results from pid . .
    // . . . . . . . . . . . . . . . .
    for(int i = 0; i < test_samples; i++) {
        switch(i) {
            case 0:
            printf("reset..\n");
            break;
            case 1:
            printf("\nsetpoint 0\n");
            break;
            case 5:
            printf("\nsetpoint 69\n");
            break;
            case 25:
            printf("\nsetpoint 50\n");
            break;
            case 45:
            printf("\nsetpoint 25\n");
            break;
            case 65:
            printf("\nsetpoint 95\n");
            break;
            case 85:
            printf("\nsetpoint 0\n");
            break;
            default:
            if(i % 5 == 0) printf("\n");
        }
        printf("\t%i", (int)results_plant[i]);
    }

    return 0;
}
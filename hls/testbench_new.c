#include <stdlib.h>
#include <time.h>
#include "HLS/stdio.h"
#include "pid_input.h"
#include "proportional.h"
#include "integral.h"
#include "derivative.h"
#include "pid_output.h"

#define test_samples 105

plant_t plant = 0;
sensor_t sensor = 0;

void process_plant_value(plant_t value) {
    double v = value.to_double();
    if(value > 50) {
        v = v * 0.8;
        value = v;
    }
    plant = plant + (int)value;
}

void create_sensor_value()

int main(void) {
    bool reset = true;
    short sp;
    pid_t sv = 0;
    pid_struct results_input[test_samples];
    pid_struct results_p[test_samples];
    pid_struct results_i[test_samples];
    pid_struct results_d[test_samples];
    plant_t results[test_samples];
    float settings[NR_ARGS] = {
        0.01f,                           // update frequency (seconds)
        0.12f,                           // proportional gain
        0.68f,                           // integral gain
        1.1f                             // derivative gain
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
        pid_input(settings, sp, sv, reset);

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
        ihc_hls_enqueue(&results[i], &pid_output, pid_output_in);
        ihc_hls_component_run_all(pid_output);

        // TODO simulate sensor value(sv) and do some process value conversion between plant and sensor.
        // this should also be implemented in HW.... when some sensor and actuator is known....
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
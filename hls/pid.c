/** pid
 * a generic pid regulator.
 */

#include "pid.h"
#include "HLS/stdio.h"

pid_t divide(pid_t a, pid_t b) {
    return a / b;
}

pid_t multiply(pid_t a, pid_t b) {
    return a * b;
}

hls_avalon_slave_component component
plant_t pid(hls_avalon_slave_memory_argument(NR_ARGS*sizeof(float)) float* settings,
         hls_avalon_slave_register_argument short setpoint,
         pid_t sensor_value,
         bool reset) {
    static pid_t last_error = 0.0, integral_total = 0.0;
    pid_t Gp, Gi, Gd, p, i, d, error, min, max, freq, tmp;
    pid_t ret = 0.0, sp = setpoint;

    // set floating point values to fixed point values.
    Gp = settings[0];
    Gi = settings[1];
    Gd = settings[2];
    min = settings[3];
    max = settings[4];
    freq = settings[5];

    // if reset is active
    if(reset) {
        integral_total = 0;
        last_error = 0;
    }

    // calculate current error
    error = sp - sensor_value;

    // calculate result for p
    p = multiply(Gp, error);

    // calculate result for i
    tmp = multiply(Gi, error);
    i = integral_total + (multiply(tmp, freq));

    // calculate result for d
    // use at own risk, make sure to have a filter from sensor. noice will be amplified with derivative.
    d = multiply(Gd, ((error - last_error) / freq));

    // set return value
    if(i > CLAMP_HIGH_LIMIT || i < CLAMP_LOW_LIMIT) {
        integral_total = 0;
        ret = p + d;
    } else {
        ret = p + i + d;
    }

    // set current error to last error
    last_error = error;

    // set integral total to i
    integral_total = integral_total + i;

    // return value
    if(ret > max) {
        ret = max;
    } else if(ret < min) {
        ret = min;
    }

    printf("error = %f\n", error.to_double());
    printf("proportional = %f\n", p.to_double());
    printf("integral = %f\n", i.to_double());
    printf("derivative = %f\n", d.to_double());
    printf("return value = %f\n", ret.to_double());
    printf("=======================\n\n");
    return ret.to_ac_int();
}


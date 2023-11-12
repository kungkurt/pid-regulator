/** pid
 * a generic pid regulator.
 */

#include "pid.h"

hls_avalon_slave_component
component void pid(hls_avalon_slave_memory_argument(NR_SETTINGS*sizeof(float)) float* settings,
                   hls_avalon_slave_register_argument unsigned short setpoint,
                   sensor_t sensor_value,
                   bool reset) {
    static pid_t last_error = 0, integral_total = 0;
    pid_t Gp, Gi, Gd, p, i, d, error, min, max, freq;
    plant_t ret;
    sp_t sp = setpoint;

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
    p = Gp * error;

    // calculate result for i
    i = integral_total + (Gi * error * freq);

    // calculate result for d
    // use at own risk, make sure to have a filter from sensor. noice will be amplified with derivative.
    d = Gd * ((error - last_error) / freq);

    // set return value
    if(i > CLAMP_HIGH_LIMIT) {
        ret = p + CLAMP_HIGH_LIMIT + d;
    } else if(i < CLAMP_LOW_LIMIT) {
        ret = p + CLAMP_LOW_LIMIT + d;
    } else {
        ret = p + i + d;
    }

    // set current error to last error
    last_error = error;

    // set integral total to i
    integral_total = i;

    // return value
    if(ret > max) {
        return max;
    } else if(ret < min) {
        return min;
    } else {
        return ret;
    }
}
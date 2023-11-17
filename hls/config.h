#ifndef CONFIG_H_
#define CONFIG_H_

#include "HLS/hls.h"
#include "HLS/ac_int.h"
#include "HLS/ac_fixed.h"

#define NR_ARGS 4

typedef ac_fixed<19, 9, true> pid_t;                            // type for pid data.          (10 bits of decimals means LSB is 0.0009765625)
typedef ac_fixed<14, 3, false> freq_t;                          // type for update frequency.  (in seconds)
typedef ac_int<8, false> plant_t;                               // type for plant data.        (the plant is the actuator)
typedef ac_int<12, false> sensor_t;                             // type for sensor data.       (12-bit is the onboard adc, i dont know)

struct pid_struct {
    bool reset,
    pid_t error,
    freq_t freq,
    pid_t Gp,
    pid_t Gi,
    pid_t Gd,
    pid_t p,
    pid_t i,
    pid_t d
};

#endif
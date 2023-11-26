#ifndef CONFIG_H_
#define CONFIG_H_

#include "HLS/hls.h"
#include "HLS/ac_int.h"
#include "HLS/ac_fixed.h"

#define NR_ARGS 4

typedef ac_fixed<17, 8, true> pid_t;                            // type for pid data.          (10 bits of decimals means LSB is 0.0009765625)
typedef ac_fixed<12, 3, false> freq_t;                          // type for update frequency.  (in seconds)
typedef ac_fixed<17, 8, true> sensor_t;                         // type for sensor data.
typedef ac_fixed<17, 8, true> plant_t;                          // type for plant data.        (the plant is the actuator)

struct p_struct {
    bool reset;
    pid_t error;
    pid_t Gp;
};

struct i_struct {
    bool reset;
    freq_t freq;
    pid_t error;
    pid_t Gi;
};

struct d_struct {
    bool reset;
    freq_t freq;
    pid_t error;
    pid_t Gd;
};

#endif
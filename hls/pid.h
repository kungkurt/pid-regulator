#ifndef PID_H_
#define PID_H_

#include "HLS/hls.h"
#include "HLS/ac_int.h"
#include "HLS/ac_fixed.h"

#define NR_ARGS          6
#define CLAMP_LOW_LIMIT  75
#define CLAMP_HIGH_LIMIT 511

typedef ac_fixed<32, 12, true> pid_t;                           // type for pid_controller
typedef ac_int<12, true> plant_t;

hls_avalon_slave_component component
plant_t pid(hls_avalon_slave_memory_argument(NR_ARGS*sizeof(float)) float* settings,
            hls_avalon_slave_register_argument short setpoint,
            pid_t sensor_value,
            bool reset);

#endif
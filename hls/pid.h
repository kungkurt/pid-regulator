#ifndef PID_H_
#define PID_H_

#include "HLS/hls.h"
#include "HLS/ac_int.h"
#include "HLS/ac_fixed.h"

#define NR_SETTINGS      6
#define CLAMP_LOW_LIMIT  75
#define CLAMP_HIGH_LIMIT 511

typedef ac_int<16, false> sp_t;                                 // type for setpoint
typedef ac_int<12, false> sensor_t;                             // type for sensor
typedef ac_fixed<32, 10, true> pid_t;                           // type for p, i and d
typedef ac_int<10, false> plant_t;                              // type for plant

component void pid(hls_avalon_slave_memory_argument(NR_SETTINGS*sizeof(float)) float* settings,
                   hls_avalon_slave_register_argument unsigned short setpoint,
                   sensor_t sensor_value,
                   bool reset);

#endif
#include <HLS/hls.h>
#include <ac_int.h>
#include <ac_fixed.h>

typedef ac_int<1, false> bool_t;                                // bool type
typedef ac_int<16, false> sp_t;                                 // type for setpoint
typedef ac_int<12, false> sensor_t;                             // type for sensor
typedef ac_fixed<64, 16, true> pid_t;                           // type for p, i and d
typedef ac_fixed<32, 8, false> freq_t;                          // type for update frequency in seconds

typedef struct {
    pid_t p;
    pid_t i;
    pid_t d;
    pid_t limit_min;
    pid_t limit_max;
    freq_t freq;
} pid_hw;

typedef struct {
    double p;
    double i;
    double d;
    double limit_min;
    double limit_max;
    float freq;
} pid_settings;
#include "pid_output.h"

hls_always_run_component component
void pid_output(ihc::stream_in<pid_t>& pin,
                ihc::stream_in<pid_t>& iin,
                ihc::stream_in<pid_t>& din,
                hls_avalon_slave_memory_argument(LOG_SIZE*sizeof(short int)) short int* result) {

    // declare variables.
    pid_t p = pin.read();
    pid_t i = iin.read();
    pid_t d = din.read();

    // calculate current result value.
    plant_t current = (p + i + d).to_ac_int();

    // left shift all results so current result is always the first element.
    #pragma unroll 2
    for(unsigned char j = LOG_SIZE-1; j > 0; j--) {
        result[j] = result[j-1];
    }
    result[0] = current.to_int();
}
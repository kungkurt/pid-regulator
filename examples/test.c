/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <altera_timer_regs.h>
#include "pid_driver.h"

#define setpoint 0xFA21

void pid_write_to(float* settings) {
  float* buffer = (float*)IN_PID_PID_INPUT_INTERNAL_INST_AVS_SETTINGS_BASE;
  for(alt_u16 i = 0; i < 4; i++) {
    *buffer = *settings;
    settings++;
    buffer++;
  }
}

float get_offset(void) {
	float ret = 0.0;
	TIMER_RESET;
	TIMER_START;
	ret = TIMER_READ;
	TIMER_RESET;

	return ret;
}

int main() {
  // declare time variables
  float offset = get_offset();
  float hw_timer = 0.0f;

  // disable interrupts
  pid_disable_interrupt();
  pid_clear_done_register();

  // pid controller settings
  pid_setpoint(setpoint);
  float pid_settings[4] = {
	0.10f,                            // update frequency (seconds)
	0.699f,                           // proportional gain
	0.347f,                           // integral gain
	0.066f                            // derivative gain
  };
  pid_write_to(pid_settings);
  while(pid_busy());

  // time hw pid controller.
  TIMER_RESET;
  TIMER_START;
  pid_run();
  while(!(pid_done()));
  hw_timer = (TIMER_READ - offset) / 50000000;
  printf("exec time: %f", hw_timer);
  TIMER_RESET;

  // exit program.
  return 0;
}

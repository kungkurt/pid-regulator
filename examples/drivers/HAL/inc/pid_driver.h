/*
 * pid_driver.h
 *
 *  Created on: 26 nov. 2023
 *      Author: mathias
 */

#ifndef PID_DRIVER_H_
#define PID_DRIVER_H_

#include <system.h>
#include <io.h>
#include <alt_types.h>

/******************************************************************************/
/* Memory Map Summary                                                         */
/******************************************************************************/

/*
  Register  | Access  |   Register Contents      | Description
  Address   |         |      (64-bits)           |
------------|---------|--------------------------|-----------------------------
        0x0 |       R |         {reserved[62:0], |     Read the busy status of
            |         |               busy[0:0]} |               the component
            |         |                          |  0 - the component is ready
            |         |                          |       to accept a new start
            |         |                          |    1 - the component cannot
            |         |                          |          accept a new start
------------|---------|--------------------------|-----------------------------
        0x8 |       W |         {reserved[62:0], |  Write 1 to signal start to
            |         |              start[0:0]} |               the component
------------|---------|--------------------------|-----------------------------
       0x10 |     R/W |         {reserved[62:0], |      0 - Disable interrupt,
            |         |   interrupt_enable[0:0]} |        1 - Enable interrupt
------------|---------|--------------------------|-----------------------------
       0x18 |  R/Wclr |         {reserved[61:0], | Signals component completion
            |         |               done[0:0], |       done is read-only and
            |         |   interrupt_status[0:0]} | interrupt_status is write 1
            |         |                          |                    to clear
------------|---------|--------------------------|-----------------------------
       0x20 |     R/W |         {reserved[47:0], |           Argument setpoint
            |         |          setpoint[15:0]} |

NOTE: Writes to reserved bits will be ignored and reads from reserved
      bits will return undefined values.
*/


/******************************************************************************/
/* Register Address Macros                                                    */
/******************************************************************************/

/* Byte Addresses */
#define PID_INPUT_CSR_BUSY_REG					(0x0)
#define PID_INPUT_CSR_START_REG					(0x8)
#define PID_INPUT_CSR_INTERRUPT_ENABLE_REG		(0x10)
#define PID_INPUT_CSR_INTERRUPT_STATUS_REG		(0x18)
#define PID_INPUT_CSR_ARG_SETPOINT_REG			(0x20)

/* Argument Sizes (bytes) */
#define PID_INPUT_CSR_ARG_SETPOINT_SIZE			(2)

/* Argument Masks */
#define PID_INPUT_CSR_ARG_SETPOINT_MASK			(0xffff)

/* Status/Control Masks */
#define PID_INPUT_CSR_BUSY_MASK					(1<<0)
#define PID_INPUT_CSR_BUSY_OFFSET				(0)

#define PID_INPUT_CSR_START_MASK				(1<<0)
#define PID_INPUT_CSR_START_OFFSET				(0)

#define PID_INPUT_CSR_INTERRUPT_ENABLE_MASK		(1<<0)
#define PID_INPUT_CSR_INTERRUPT_ENABLE_OFFSET	(0)

#define PID_INPUT_CSR_INTERRUPT_STATUS_MASK		(1<<0)
#define PID_INPUT_CSR_INTERRUPT_STATUS_OFFSET	(0)
#define PID_INPUT_CSR_DONE_MASK					(1<<1)
#define PID_INPUT_CSR_DONE_OFFSET				(1)

// read and write functions
#define pid_read(offset)						IORD_32DIRECT(IN_PID_PID_INPUT_INTERNAL_INST_AVS_CRA_BASE, offset)
#define pid_write(offset, data)					IOWR_32DIRECT(IN_PID_PID_INPUT_INTERNAL_INST_AVS_CRA_BASE, offset, data)

// control macros
#define pid_disable_interrupt()					pid_write(PID_INPUT_CSR_INTERRUPT_ENABLE_REG, PID_INPUT_CSR_INTERRUPT_ENABLE_MASK & 0x1)
#define pid_enable_interrupt()					pid_write(PID_INPUT_CSR_INTERRUPT_ENABLE_REG, PID_INPUT_CSR_INTERRUPT_ENABLE_MASK & 0x0)
#define pid_clear_done_register()				pid_write(PID_INPUT_CSR_INTERRUPT_STATUS_REG, PID_INPUT_CSR_INTERRUPT_STATUS_MASK & 0x1)
#define pid_run()								pid_write(PID_INPUT_CSR_START_REG, PID_INPUT_CSR_START_MASK & 0x1)
#define pid_done()								pid_read(PID_INPUT_CSR_INTERRUPT_STATUS_REG) & PID_INPUT_CSR_DONE_MASK
#define pid_busy()								pid_read(PID_INPUT_CSR_BUSY_REG) & PID_INPUT_CSR_BUSY_MASK
#define pid_setpoint(data)						pid_write(PID_INPUT_CSR_ARG_SETPOINT_REG, data)
#define pid_get_setpoint()						pid_read(PID_INPUT_CSR_ARG_SETPOINT_REG)

#endif /* PID_DRIVER_H_ */

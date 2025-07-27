/* ---------------------------------------------------------------------------------------
 * File        : io.h
 * Author      : Civinini Luca - IK5PWC
 *                 luca@civinini.net - http://www.civinini.net
 *                 luca@ik5pwc.it    - http://www.ik5pwc.it
 *
 * Description : This is the include file for I/O operations
 * ---------------------------------------------------------------------------------------
*/

// Define guard for this file
#ifndef io_h
#define io_h


/* ------------ Includes ------------ */
#include <Arduino.h>              // Include arduino headers
#include "params.h"               // Include program params
#include "datatypes.h"            // Include custom data types


/* ------------- Macros ------------- */
#define KEY_DEBOUNCE_MS 10        // milliseconds to wait between two key read to avoid bounces
#define WAIT_MUX_MS     5         // milliseconds to wait after changing mux status
#define ANALOG_READ_PASSES 25     // Number of analog readings to perform



/* ------------- Enum ------------- */
enum read_sensor_state_t : uint8_t {
	mux0 = 0xC0,
	mux1 = 0xC1,
	mux2 = 0xC2,
	mux3 = 0xC3
};


/* -------- Public functions --------- */
void init_pin();
key_status_t read_keys_analog();
void read_sensor (dc_out_t *dc);

#endif /* io_h */

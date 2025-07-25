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

// Simple function to return voltage from ADC using appropriate error correction
//#define VOLT(x)

//#define CURRENT(x)  ( ( ((float)x - ADC_ERR_CURRENT)) * 5 / 1023) - 2.5) * CURRENT_SENSOR_MAX /2 ));


/* ------------- Enum ------------- */
enum read_sensor_state_t : uint8_t {
	mux0 = 0xB0,
	mux1 = 0xB1,
	mux2 = 0xB2,
	mux3 = 0xB3
};


/* -------- Public functions --------- */
void init_pin();
key_status_t read_keys_analog();
void read_sensor (dc_out_t *dc);

#endif /* io_h */

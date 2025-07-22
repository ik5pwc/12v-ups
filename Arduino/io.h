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
#define WAIT_MUX_MS 5             // milliseconds to wait after changing mux status
#define WAIT_MUX_MS 10            // milliseconds between two mux reads


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
//void drive_led (operate_status_t *p_operate, settings_t *p_settings);
//void drive_relay (operate_status_t *p_operate);

#endif /* io_h */

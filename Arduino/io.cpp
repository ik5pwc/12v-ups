/* ---------------------------------------------------------------------------------------
 * File        : io.cpp
 * Author      : Civinini Luca - IK5PWC
 *                 luca@civinini.net - http://www.civinini.net
 *                 luca@ik5pwc.it    - http://www.ik5pwc.it
 *
 * Description : This is the source file for all I/O operation
 * ---------------------------------------------------------------------------------------
*/


// include header file
#include "io.h"



static float adc_voltage(uint16_t adc);
static float adc_current(uint16_t adc);

/*----------------------------------------------------------------------------------------------------------------------
 * Function: read_keys
 * -------------------------------
 * Read scrolling switch
 *
 * Invoked by:
 * . loop              (UPSMonitor.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used: NONE
 *
 * Pre Processor Macro:
 * . BUTTON            (params.h)
 * . KEY_DEBOUNCE_MS   (io.h)
 *
 * Struct: NONE
 *
 * Enum:
 * . key_status_t      (datatypes.h)
 *
 * Arguments: NONE
*/
key_status_t read_keys_analog() {
  key_status_t key_now = off;           // Temporary store new key
  uint16_t read1,read2 = 0;             // consecutive analog reads
  static key_status_t key_old  = off;   // Store the key value on previous run

  // Read Analog pin 2 times
  read1 = analogRead(BUTTON);
	delay (KEY_DEBOUNCE_MS);
  read2 = analogRead(BUTTON);

  // Validate analog reads
  if (read1 >> 2 == read2>>2 ){
    // ok two readings are "similar, take action
  	if (read1 > 1000) { key_now = on; } else {key_now = off;}

  	// Report status change only if there was an "off" between two on
  	if (key_now == on && key_old == on ) {key_now = off;} else {key_old = key_now;}
  }

  // Set key value
  return key_now;
}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: read_sensor
 * -------------------------------
 * Manage the two led for controller status
 *
 * Invoked by:
 * . loop              (switchINO.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used: NONE
 *
 * Pre Processor Macro:
 * . FAST_BLINK_MS     (io.h)
 * . SLOW_BLINK_MS     (io.h)
 * . LED_RUNNING       (params.h)
 * . LED_AUTOMODE      (params.h)
 *
 * Struct:
 * . operate_status_t  (datatypes.h)
 * . settings_t        (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . p_operate: a pointer to struct containing controller status
 * . p_settings: pointer to struct containing controller configuration
 *
*/
void read_sensor (dc_out_t *dc) {
  static read_sensor_state_t mux = mux0;
  uint16_t read[5] = {0,0,0,0,0};     // array to store analog input reads.

  // Select multiplexer
  digitalWrite (AMUX1, mux & 0x01);
  digitalWrite (AMUX2, mux & 0x02);
  delay(WAIT_MUX_MS);                   // time propagation for CD4052a

  // Perform multiple readings for each input
  for (uint8_t i=0; i<ANALOG_READ_PASSES ; i++) {read[0] += analogRead(A0);}
  read[0] = read[0]/ANALOG_READ_PASSES;

  for (uint8_t i=0; i<ANALOG_READ_PASSES ; i++) {read[1] += analogRead(A1);}
  read[1] = read[1]/ANALOG_READ_PASSES ;

  for (uint8_t i=0; i<ANALOG_READ_PASSES ; i++) {read[2] += analogRead(A2);}
  read[2] = read[2]/ANALOG_READ_PASSES;

  for (uint8_t i=0; i<ANALOG_READ_PASSES ; i++) {read[3] += analogRead(A3);}
  read[3] = read[3]/ANALOG_READ_PASSES;

  for (uint8_t i=0; i<ANALOG_READ_PASSES ; i++) {read[4] += analogRead(A4);}
  read[4] = read[4]/ANALOG_READ_PASSES;

  // Battery voltage are always present
  dc->m1_vbat = adc_voltage(read[2]) * SCALE_VOLTAGE;
  dc->m2_vbat = adc_voltage(read[3]) * SCALE_VOLTAGE;
  dc->m3_vbat = adc_voltage(read[4]) * SCALE_VOLTAGE;

  // compute other values
  switch (mux) {
    case mux0 :
    	if (read[0] != 0 ) {dc->m2_ibat = adc_current(read[0]) * SCALE_M2_IBAT;} else {dc->m2_ibat = 0;}
    	if (read[1] != 0 ) {dc->m1_ibat = adc_current(read[1]) * SCALE_M1_IBAT;} else {dc->m1_ibat = 0;}
    	break;
    case mux1 :
    	if (read[0] != 0 ) {dc->m2_iout = adc_current(read[0]) * SCALE_M2_IOUT;} else {dc->m2_iout = 0;}
    	if (read[1] != 0 ) {dc->m3_ibat = adc_current(read[1]) * SCALE_M3_IBAT;} else {dc->m3_ibat = 0;}
      break;
    case mux2 :
    	if (read[0] != 0 ) {dc->m1_iout = adc_current(read[0]) * SCALE_M1_IOUT;} else {dc->m1_iout = 0;}
    	if (read[1] != 0 ) {dc->m3_iout = adc_current(read[1]) * SCALE_M3_IOUT;} else {dc->m3_iout = 0;}
  	  break;
    case mux3 :
  	  dc->ps_vout  = adc_voltage(read[0]) * SCALE_VOLTAGE;
  	  dc->ups_vout = adc_voltage(read[1]) * SCALE_VOLTAGE;
  	  break;
  }

  // Compute total current and power
  dc->ups_itot = dc->m1_iout + dc->m2_iout + dc->m3_iout;
  dc->ups_pwr = dc->ups_itot * dc->ups_vout;

  // move to next mux
  if (mux == mux3) {mux = mux0; } else {mux = mux +1;}
}


/*----------------------------------------------------------------------------------------------------------------------
 * Function: adc_voltage
 * -------------------------------
 * Return voltage measured from ADC, including factor correction
 *
 * Invoked by:
 * . read_sensor        (io.cpp)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used: NONE
 *
 * Pre Processor Macro:
 * . ADC_ERR_VOLTAGE    (params.h)
 *
 * Struct: NONE
 *
 * Enum: NONE
 *
 * Arguments:
* . adc: the value from ADC
*/
float adc_voltage(uint16_t adc) { return ((float)adc - ADC_ERR_VOLTAGE ) * 5 / 1023;}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: adc_current
 * -------------------------------
 * Return current measured from ADC, including factor correction
 *
 * Invoked by:
 * . read_sensor        (io.cpp)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used: NONE
 *
 * Pre Processor Macro:
 * . ADC_ERR_CURRENT    (params.h)
 * . CURRENT_SENSOR_MAX (params.h)
 *
 * Struct: NONE
 *
 * Enum: NONE
 *
 * Arguments:
 * . adc: the value from ADC
*/
float adc_current(uint16_t adc) {return ((( (float)adc - ADC_ERR_CURRENT ) * 5 / 1023) - 2.5) * CURRENT_SENSOR_MAX /2 ;}



 /*----------------------------------------------------------------------------------------------------------------------
 * Function: init_pin
 * -------------------------------
 * Initialize Arduino PIN
 *
 * Invoked by:
 * . setup              (UPSMonitor.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used: NONE
 *
 * Pre Processor Macro:
 * . AMUX1             (params.h)
 * . AMUX1             (params.h)
 *
 * Struct: NONE
 *
 * Enum: NONE
 *
 * Arguments: NONE
*/
void init_pin() {
  analogReference(INTERNAL); //set reference voltage to internal

  // Switch output
  pinMode (AMUX1, OUTPUT);
  pinMode (AMUX2, OUTPUT);
  pinMode (AMUX1, LOW);
  pinMode (AMUX2, LOW);

  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (A4, INPUT);

}

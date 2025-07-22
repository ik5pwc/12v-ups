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
  	if (read1 < 100) { key_now = on; } else {key_now = off;}

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
 * +--------------------------------+--------------+------------------------------+
 * |    CONTROLLER STATUS           | LED_RUNNING  | LED_AUTOMODE                 |
 * +--------------------------------+--------------+------------------------------+
 * | Configuration mode             | BLINK normal | OFF                          |
 * | Manual mode                    | BLINK normal | OFF                          |
 * | Normal Operation               | BLINK normal | ON                           |
 * | All antennas disconnected      | BLINK fast   | BLINK fast (alternate)       |
 * | No freq/invalid band           | BLINK fast   | ON/OFF based on current mode |
 * | No antenna for selected band   | BLINK fast   | BLINK slow                   |
 * +--------------------------------+--------------+------------------------------+
*/
void read_sensor (dc_out_t *dc) {
  static read_sensor_state_t mux = mux0;
  uint16_t read[5] = {0,0,0,0,0};     // array to store analog input reads.

  // Select multiplexer
  digitalWrite(AMUX1, mux & 0x01);
  digitalWrite(AMUX2, mux & 0x02);
  delay (WAIT_MUX_MS);

  // Read analog data - 1st pass
  Serial.println("inizio");
  read[4] = analogRead(A4); delay(10);
  read[3] = analogRead(A3); delay(10);
  read[2] = analogRead(A2); delay(10);
  read[0] = analogRead(A0); delay(10);
  read[1] = analogRead(A1); delay(10);

  // Save values in global array
  if (read[2] != 1023) {dc->m1_vbat = VOLT(read[2]) * SCALE_VOLTAGE;}
  if (read[3] != 1023) {dc->m2_vbat = VOLT(read[3]) * SCALE_VOLTAGE;}
  if (read[4] != 1023) {dc->m3_vbat = VOLT(read[4]) * SCALE_VOLTAGE;}

  // compute other values
  switch (mux) {
    case mux0 :
    	dc->m2_ibat = read[0] * SCALE_M1_IOUT;
    	dc->m1_ibat = read[1] * SCALE_M3_IOUT;
    	break;
    case mux1 :
      dc->m2_iout = read[0] * SCALE_M1_IOUT;
      dc->m3_ibat = read[1] * SCALE_M3_IBAT;
      break;
    case mux2 :
  	  dc->m1_iout = read[0] * SCALE_M2_IOUT;
  	  dc->m3_iout = read[1] * SCALE_M3_IOUT;
  	  break;
    case mux3 :
  	  dc->ps_vout  = VOLT(read[0]) * SCALE_VOLTAGE;
  	  dc->ups_vout = VOLT(read[1]) * SCALE_VOLTAGE;
  	  break;
  }

  // Compute total current and power
  dc->ups_itot = dc->m1_iout + dc->m2_iout + dc->m3_iout;
  dc->ups_pwr = dc->ups_itot * dc->ups_vout;

  // move to next mux
  if (mux == mux3) {mux = mux0; } else {mux = mux +1;}
}




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
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (A4, INPUT);

}

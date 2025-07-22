/*
 * ---------------------------------------------------------------------------------------
 * File        : lcd_main.h
 * Author      : Civinini Luca - IK5PWC
 *                 luca@civinini.net - http://www.civinini.net
 *                 luca@ik5pwc.it    - http://www.ik5pwc.it
 *
 * Description : This is the include file for LCD operations
 * ---------------------------------------------------------------------------------------
*/

// Define guard for this file
#ifndef lcd_h
#define lcd_h


/* ------------ Includes ------------ */
#include <Arduino.h>              // Include arduino headers
#include <LiquidCrystal.h>        // Include LCD library
#include "params.h"               // Include program params
#include "datatypes.h"            // Include custom data types


/* -------- Public functions --------- */
void lcd_init();
void lcd_operate (dc_out_t *sensor, network_t *net, key_status_t *key);


/* ------------- Macros ------------- */
#define INIT_TITLE_MS  1700       // Milliseconds to display the project title
#define INIT_AUTH_MS 900          // milliseconds to display author


/* ------------- Enums ------------- */
// Define which page is currenty displayed in LCD
enum lcd_page_t : uint8_t {
  general = 0xB0,
  module1 = 0xB1,
	module2 = 0xB2,
	module3 = 0xB3,
	ip      = 0xB4,
	subnet  = 0xB5,
	gateway = 0xB6
};



#endif /* LCD_H_ */

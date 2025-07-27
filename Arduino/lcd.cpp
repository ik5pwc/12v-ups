/*
 * ---------------------------------------------------------------------------------------
 * File        : lcd.cpp
 * Author      : Civinini Luca - IK5PWC -  luca@ik5pwc.it    - http://www.ik5pwc.it
 * Created     : 2022/09/15
 * Description : Manage LCD Display
 *
 * Use this code at your own risk.
 * Code can be modified and redistributed under following  conditions:
 * 1) You should not remove any reference to original author
 * 2) Your changes must be forwarded to original  author
 * 3) Any commercial activity is forbidden
 * ---------------------------------------------------------------------------------------
*/

// Include header file
#include "lcd.h"


/* ---- Static functions (i.e. callable only within this file) ----- */
static void lcd_print_general (dc_out_t *dc);
static void lcd_print_module (dc_out_t *dc, uint8_t module);
//static void lcd_print_net (char name[], uint8_t  val[4]);
static void lcd_print_net (uint8_t type, uint8_t  val[4]);


/* ------- global variables -------- */
LiquidCrystal g_lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7); // @suppress("Abstract class cannot be instantiated")



/*----------------------------------------------------------------------------------------------------------------------
 * Function: init_lcd
 * -------------------------------
 * Initialize LCD display and prompt power on message
 *
 * Invoked by:
 * . setup             (UPSMonitor.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 * . g_lcd             (lcd.cpp)
 *
 * Pre Processor Macro:
 * . LCD_COLS          (params.h)
 * . VERSION           (params.h)
 * . INIT_AUTH_MS      (lcd.h)
 * . INIT_TITLE_MS     (lcd.h)
 *
 * Struct: NONE
 *
 * Enum: NONE
 *
 * Arguments: NONE
*/
void lcd_init() {
	// Initialize the display and clear the content
  g_lcd.begin(LCD_COLS, 2);
  g_lcd.clear();

  // Display Banner - Device name
  g_lcd.setCursor(0,0);
  g_lcd.print(F("12v Network UPS"));g_lcd.setCursor(0,1); g_lcd.print(F("Monitor"));
  delay (INIT_TITLE_MS);

  // Display Banner - Version and Author
  g_lcd.clear();g_lcd.setCursor(0,0);g_lcd.print("Version ");g_lcd.print(VERSION);
  g_lcd.setCursor(0,1);
  g_lcd.print(F("   by  IK5PWC   "));
}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: lcd_operate
 * -------------------------------
 * Main function managing LCD
 *
 * Invoked by:
 * . loop                   (UPSMonitor.ino)
 *
 * Called Sub/Functions:
 * . lcd_print_module       (lcd_main.cpp)
 * . lcd_print_general      (lcd_main.cpp)
 * . lcd_print_net          (lcd_main.cpp)
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 * . g_lcd                  (lcd_main.cpp)
 *
 * Pre Processor Macro:
 * . PAGE_TIMEOUT_SEC      (params.h)
 * . PAGE_UPDATE_SEC       (params.h)
 * . MANUAL_TIMEOUT_SCALE  (params.h)
 *
 * Struct:
 * . dc_out_t              (datatypes.h)
 * . network_t             (datatypes.h)
 * . key_status_t          (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . p_operate: a pointer to the struct managing controller status
 * . p_settings: pointer to the struct storing controller's settings
*/
void lcd_operate (dc_out_t *sensor, network_t *net, key_status_t *key, bool update) {
  static uint8_t page_timeout = 0;                   // Timer for moving to next page
  static lcd_page_t lcd_page  = general;             // LCD Page to display

  // update timer (manual page scrolling)
  if (page_timeout > 0 &&  (millis() / 1000 ) % 2 == page_timeout % 2 ) { page_timeout--;}
  if (page_timeout == 0 ) { lcd_page = general;}  // if timer expired, return to main page

  // Key button pressed ?
  if (*key == on) {
  	// Move to next page or jump to beginning if last one
  	if (lcd_page == gateway ){ lcd_page = general;} else {lcd_page = lcd_page + 1;}

  	// Reset page timeout
  	page_timeout = PAGE_TIMEOUT_SEC;
  }


  // Update LCD if refresh timer expired timer expired or key was pressed
  if ( update || *key == on ) {
  	g_lcd.clear();
    switch (lcd_page) {
    	case general: lcd_print_general (sensor); break;
    	case module1: lcd_print_module (sensor,1); break;
    	case module2: lcd_print_module (sensor,2); break;
    	case module3: lcd_print_module (sensor,3); break;
    	case ip     : lcd_print_net (0,net->ip); break;
    	case subnet : lcd_print_net (1, net->mask); break;
    	case gateway: lcd_print_net (2, net->gw); break;
  	}
  }
}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: lcd_print_general
 * -------------------------------
 * Print voltage/current for each UPS module in the following format
 *    M1 xx.yyA xxx.xW   --> Module 1 current and power out
 *    B1 aa.yyA xx.yyV   --> Battery for module 1: current and voltage
 *
 * Invoked by:
 * . lcd_operate          (lcd.cpp)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 * . g_lcd             (lcd.cpp)
 *
 * Pre Processor Macro: NONE
 *
 * Struct:
 * . dc_out_t          (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . dc: pointer to a struct for all electric data
 * . module: the module number
*/
void lcd_print_general (dc_out_t *dc) {
	// 1st row
	g_lcd.setCursor(0, 0);
	if (dc->ps_vout != 0) {g_lcd.print(F("AC Power")); } else {g_lcd.print(F("Battery")); }
  g_lcd.setCursor(10, 0);
  g_lcd.print(dc->ups_vout,2);g_lcd.print("V");

  // 2nd row
  g_lcd.setCursor(0, 1);
  g_lcd.print(dc->ups_itot,2);g_lcd.print("A ");
  g_lcd.print(dc->ups_pwr,2);g_lcd.print("W");

}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: lcd_print_module
 * -------------------------------
 * Print voltage/current for each UPS module in the following format
 *    M1 xx.yyA xxx.xW   --> Module 1 current and power out
 *    B1 aa.yyA xx.yyV   --> Battery for module 1: current and voltage
 *
 * Invoked by:
 * . lcd_operate          (lcd.cpp)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 * . g_lcd             (lcd.cpp)
 *
 * Pre Processor Macro: NONE
 *
 * Struct:
 * . dc_out_t          (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . dc: pointer to a struct for all electric data
 * . module: the module number
*/
void lcd_print_module (dc_out_t *dc, uint8_t module) {
	g_lcd.setCursor(0, 0);

	// First row
	g_lcd.print("M"); g_lcd.print(module);
	g_lcd.print (F(" Iout "));
	switch (module) {
	  case 1: g_lcd.print(dc->m1_iout,2); break;
	  case 2: g_lcd.print(dc->m2_iout,2); break;
	  case 3: g_lcd.print(dc->m3_iout,2); break;
	}
	g_lcd.print("A");

	// Second row
	g_lcd.setCursor(0, 1);
	g_lcd.print("B"); g_lcd.print(module); g_lcd.print (" ");
	switch (module) {
	  case 1: g_lcd.print(dc->m1_vbat,2); break;
	  case 2: g_lcd.print(dc->m2_vbat,2); break;
	  case 3: g_lcd.print(dc->m3_vbat,2); break;
	}
	g_lcd.print("V ");

	switch (module) {
	  case 1: g_lcd.print(dc->m1_ibat,2); break;
	  case 2: g_lcd.print(dc->m2_ibat,2); break;
	  case 3: g_lcd.print(dc->m3_ibat,2); break;
	}
  g_lcd.print("A");
}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: lcd_print_net
 * -------------------------------
 * Print network information on 2 lines
 *
 * Invoked by:
 * . lcd_operate          (lcd.cpp)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 * . g_lcd             (lcd.cpp)
 *
 * Pre Processor Macro: NONE
 *
 * Struct: NONE
 *
 * Enum: NONE
 *
 * Arguments:
 * . type: integer to set the tile (0: ip address, 1: subnet mask, 2: Gateway)
 * . value: an array of 4 integer representing IP/subnet or gateway
*/
static void lcd_print_net (uint8_t type, uint8_t  val[4]) {
	// First row
	g_lcd.setCursor(0, 0);
	switch (type) {
	  case 0: g_lcd.print(F("IP Address")); break;
	  case 2: g_lcd.print(F("Subnet mask")); break;
	  case 3: g_lcd.print(F("Gateway")); break;
	}

	// Second row
	g_lcd.setCursor(0, 1);
	for (uint8_t i=0; i<3 ; i++) {g_lcd.print(val[i]);g_lcd.print(".");}
	g_lcd.print(val[3]);
}

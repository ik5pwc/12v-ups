/* ---------------------------------------------------------------------------------------
 * File        : params.h
 * Author      : Civinini Luca - IK5PWC
 *                 luca@civinini.net - http://www.civinini.net
 *                 luca@ik5pwc.it    - http://www.ik5pwc.it
 *
 * Description : This .h file contains all configurable parameters used in the project.
 *               It must be included in every .cpp/.h file
 * ---------------------------------------------------------------------------------------
*/


// Define guard for this file
#ifndef params_h
#define params_h

// Include arduino header
#include <Arduino.h>



/* ----------------------------------------------------------------------------------------------------------------
 *                                             PARAMS CONFIGURATION STARTS
 * ----------------------------------------------------------------------------------------------------------------
 */

#define ENABLE_DHCP true                    /* true: use DHCP Server and failback to static if none available
                                             * false: use only static
                                             * NOTE: DHCP is probed periodically and assigned IP takes precedence
                                             * over failback one.
                                             */


const uint8_t static_ip[]   = {192,168,255,100};    // IP Address - used also as failback if DHCP is unavailable
const uint8_t static_mask[] = {255,255,255,100};    // Subnet mask - used also as failback if DHCP is unavailable
const uint8_t static_gw[]   = {192,168,255,1};      // Gateway - used also as failback if DHCP is unavailable




// How many antenna to switch (max 9 due to BCD coding)
#define ANT_COUNT 6

// How many ham bands
// When changing this number, please update band definition in datatypes.h
#define HAM_BANDS 12


// Input LCD pins
// Uses 4 pin (i.e. 4 bit nibble)
#define LCD_RS A0                    // LCD Definition - R/S PIN
#define LCD_EN A1                    // LCD Definition - Enable PIN
#define LCD_D4 A2                    // LCD Data 4
#define LCD_D5 A3                    // LCD Data 5
#define LCD_D6 A4                    // LCD Data 6
#define LCD_D7 A5                    // LCD Data 7

// LCD size
#define LCD_COLS 16                  // number of columns (min 16)
                                     // A Larger display (i.e. 2x20) can use longer antenna name

#define ANT_NAME_LEN (LCD_COLS - 4)  // This is a derived param based on LCD column number

// Switch buttons
#define BTN_UP   2                  // Up button
#define BTN_DOWN 3                  // Down button
#define BTN_ESC  4                  // Esc button (used in menu)
#define BTN_MENU 5                  // Menu button (enter and navigate in configs)

// Output LED
#define LED_RUNNING  6
#define LED_AUTOMODE 7

// CI-V input PIN
// these are FIXED due to AltSoftSerial Usage
// Declared here just for reading
#define ALTSERIAL_RX 8
#define ALTSERIAL_TX 9

// Output PIN (BCD coding)
#define OUT1 10                      // Output pins for BCD out - LSB
#define OUT2 11                      // Output pins for BCD out
#define OUT3 12                      // Output pins for BCD out
#define OUT4 13                      // Output pins for BCD out - MSB


// list of valid chars to be used within antenna names
const char allowed_chars [] PROGMEM ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 1234567890 +-*/)(&%.,<>^#@"};


/* ----------------------------------------------------------------------------------------------------------------
 *                                              PARAMS CONFIGURATION END
 * ----------------------------------------------------------------------------------------------------------------
 */

#define VERSION "2.2b"               // Program version

// end of define guard
#endif

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


// Define where server will listen
#define PORT 23



// Input LCD pins
// Uses 4 pin (i.e. 4 bit nibble)
#define LCD_RS D2                    // LCD Definition - R/S PIN
#define LCD_EN D3                    // LCD Definition - Enable PIN
#define LCD_D4 D4                    // LCD Data 4
#define LCD_D5 D5                    // LCD Data 5
#define LCD_D6 D6                    // LCD Data 6
#define LCD_D7 D7                    // LCD Data 7

// LCD size
#define LCD_COLS 16                  // number of columns (min 16)
                                     // A Larger display (i.e. 2x20) can use longer antenna name


// Scaling factors for readings - adjust based on resistor values and current sensos
#define SCALE_M1_IOUT  1   // Module 1: Load Current
#define SCALE_M1_IBAT  1       // Module 1: Battery Current
#define SCALE_M1_VBAT  0.232   // Module 1: Battery Voltage
#define SCALE_M2_IOUT  1   // Module 2: Load Current
#define SCALE_M2_IBAT  0.232   // Module 2: Battery Current
#define SCALE_M2_VBAT  1   // Module 2: Battery Voltage
#define SCALE_M3_IOUT  1   // Module 3: Load Current
#define SCALE_M3_IBAT  0.232   // Module 3: Battery Current
#define SCALE_M3_VBAT  0.232   // Module 3: Battery Voltage
#define SCALE_UPS_VOUT 0.232   // General : Load Voltage
#define SCALE_PS_VOUT  0.232   // General : Power Supply Voltage


// Switch buttons
#define BTN_UP   2                  // Up button
#define BTN_DOWN 3                  // Down button


// Output PIN dor driving multiplexer
#define AMUX1 10                      // Output pins for BCD out - LSB
#define AMUX2 11                      // Output pins for BCD out


/* ----------------------------------------------------------------------------------------------------------------
 *                                              PARAMS CONFIGURATION END
 * ----------------------------------------------------------------------------------------------------------------
 */

#define VERSION "0.5"               // Program version

// end of define guard
#endif

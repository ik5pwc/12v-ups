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
#define LCD_D4 2                    // LCD Data 4
#define LCD_D5 3                    // LCD Data 5
#define LCD_D6 4                    // LCD Data 6
#define LCD_D7 5                    // LCD Data 7
#define LCD_EN 6                    // LCD Definition - Enable PIN
#define LCD_RS 7                    // LCD Definition - R/S PIN

// LCD size
#define LCD_COLS 16                 // number of columns (min 16)
#define PAGE_TIMEOUT_SEC 30         // how many seconds remains in specific lcd page (max 250 sec)

#define DATA_REFRESH 4              // how often refresh data to lcd, telnet or MQTT (min 3, max 250 sec)


// Scaling factors for readings - adjust based on resistor values and current sensos
#define ADC_ERR_VOLTAGE     30      // QTY to sum or subctract from ADC value to make it read right values (for voltages)
                                    // To be defined experimentally comparing ADC readout with input value

#define ADC_ERR_CURRENT     15      // QTY to sum or subctract from ADC value to make it read right values (for current)
                                    // To be defined experimentally comparing ADC readout with input value

#define CURRENT_SENSOR_MAX  10      // Max current reading for specified sensor

#define SCALE_VOLTAGE       4.15    // Based on voltage partition formula + experimental adj
                                    // Compare input voltage with one from partition

// Used if current sensor is place reversed regarding current flow
#define SCALE_M1_IOUT  -1           // Module 1: Load Current
#define SCALE_M1_IBAT  -1           // Module 1: Battery Current
#define SCALE_M2_IOUT  -1           // Module 2: Load Current (reverse)
#define SCALE_M2_IBAT  -1           // Module 2: Battery Current
#define SCALE_M3_IOUT  -1           // Module 3: Load Current
#define SCALE_M3_IBAT  -1           // Module 3: Battery Current

// Switch buttons
#define BUTTON   A5                 // Button PIN

// Output PIN dor driving multiplexer
#define AMUX1 8                     // Multiplexer A pin
#define AMUX2 9                     // Multiplexer B pin


#define MQTTSUPPORT  1              // Set to 1 to enable MQTT

// MQTT Broker settings
#define MQTTBROKER   "192.168.95.124"
#define MQTTPORT     1883

// MQTT Root topic & client ID
#define MQTTTOPIC    "home/net/dcups"
#define MQTTCLIENTID "net-dc-ups"

#define DEBUG 0                       // SET TO 0 OUT TO REMOVE TRACES



/* ----------------------------------------------------------------------------------------------------------------
 *                                              PARAMS CONFIGURATION END
 * ----------------------------------------------------------------------------------------------------------------
 */



#define VERSION "1.1"               // Program version

// end of define guard
#endif

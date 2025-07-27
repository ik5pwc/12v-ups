/* ---------------------------------------------------------------------------------------
 * File        : datatypes.h
 * Author      : Civinini Luca - IK5PWC
 *               luca@ik5pwc.it
 *               http://www.ik5pwc.it
 *
 * Description : This .h file contains custom data types used within the project.
 * ---------------------------------------------------------------------------------------
*/


// Define guard for this file
#ifndef dt_h
#define dt_h

// Include arduino header
#include <Arduino.h>
#include "params.h"



/* ----------------------------------------------------------------------------------------------------------------
 *                                                ENUMs
 * ----------------------------------------------------------------------------------------------------------------
*/

// Define how IP address was assigned to device
enum dhcp_status_t : uint8_t {
  manual     = 0xA0,
  dynamic    = 0xA2,
	assigned   = 0xA4,
	fallback   = 0xA8
};


// Enum for button status
enum key_status_t : uint8_t {
  off     = 0x20,
  on      = 0x21,
};


/* ----------------------------------------------------------------------------------------------------------------
 *                                               STRUCTs
 * ----------------------------------------------------------------------------------------------------------------
*/

// all network-related stuff
struct network_t {
  uint8_t     ip[4]   = {0,0,0,0};      // Static or failback IP Address
  uint8_t     mask[4] = {0,0,0,0};      // Static or failback subnet mask
  uint8_t     gw[4]   = {0,0,0,0};      // Static or failback gateway
  uint8_t     mac[6]  = {0,0,0,0};      // Device mac address (computer on startup)
  dhcp_status_t  dhcp = dynamic;        // Track how the address was assigned
  uint16_t dhcp_timer = 0 ;             // DHCP Timer for rebind/renew
};


// Readings / scaling factor
struct dc_out_t {
	float m1_iout = 0;
	float m1_ibat = 0;
	float m1_vbat = 0;
	float m1_pwr  = 0;
	float m2_iout = 0;
	float m2_ibat = 0;
	float m2_vbat = 0;
	float m2_pwr  = 0;
	float m3_iout = 0;
	float m3_ibat = 0;
	float m3_vbat = 0;
	float m3_pwr  = 0;
	float ups_vout = 0;
	float ups_itot = 0;
	float ups_pwr = 0;
	float ps_vout = 10;
};


// Define custom debug
#if DEBUG
#define D_begin(...) Serial.begin(__VA_ARGS__);
#define D_print(...)    Serial.print(__VA_ARGS__)
#define D_write(...)    Serial.write(__VA_ARGS__)
#define D_println(...)  Serial.println(__VA_ARGS__)
#else
#define D_begin(...)
#define D_print(...)
#define D_write(...)
#define D_println(...)
#endif



// end of define guard
#endif

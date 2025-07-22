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
	float m1_iout = 11.345;
	float m1_ibat = 12.345;
	float m1_vbat = 13.345;
	float m1_pwr  = 113.3;
	float m2_iout = 14.6530;
	float m2_ibat = 11.34440;
	float m2_vbat = 12.3450;
	float m2_pwr  = 111.3;
	float m3_iout = 4.567;
	float m3_ibat = 1.03;
	float m3_vbat = 30;
	float m3_pwr  = 3.3;
	float ups_vout = 11.34524;
	float ups_itot = 22.34524;
	float ups_pwr = 1233.44;
	float ps_vout = 10;
};




/* ----------------------------------------------------------------------------------------------------------------
 *                                    CONSTs (SCALING FACTORS)
 * ----------------------------------------------------------------------------------------------------------------
*/


/*
const hamband_t  hambands[HAM_BANDS +1] PROGMEM = {
  {.meters = 0  , .f_start = 0    ,  .f_end = 0      },   // INVALID: returned when frequency is out any band
  {.meters = 160, .f_start = 1800 ,  .f_end = 1900   },   // 160M
  {.meters = 80 , .f_start = 3500 ,  .f_end = 3800   },   // 80M
  {.meters = 40 , .f_start = 7000 ,  .f_end = 7200   },   // 40M
  {.meters = 30 , .f_start = 10100,  .f_end = 10150  },   // 30M
  {.meters = 20 , .f_start = 14000,  .f_end = 14350  },   // 20M
  {.meters = 17 , .f_start = 18068,  .f_end = 18168  },   // 17M
  {.meters = 15 , .f_start = 21000,  .f_end = 21450  },   // 15M
  {.meters = 13 , .f_start = 24890,  .f_end = 24990  },   // 13M
  {.meters = 10 , .f_start = 28000,  .f_end = 29700  },   // 10M
  {.meters = 6  , .f_start = 50000,  .f_end = 51000  },   // 6M
  {.meters = 4  , .f_start = 70100,  .f_end = 70300  },   // 4M
  {.meters = 2  , .f_start = 144000, .f_end = 146000 }    // 2M
};
*/
// end of define guard
#endif

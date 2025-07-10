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

enum dhcp_status_t : uint8_t {
  manual     = 0xA0,
  dynamic    = 0xA2,
	assigned   = 0xA4,
	fallback   = 0xA8
};








// Enum for controller state machine
enum operate_states_t : uint8_t {
  oper_auto      = 0xA0,     // Antenna selection driven by CAT
  oper_manual    = 0xA3,     // Antenna selection driven by manual switches
  oper_config    = 0xA4,
  oper_cfg_start = 0xA6,
  oper_cfg_end   = 0xC6
};

enum configure_states_t : uint8_t {
  cfg_null        = 0xB0,
  cfg_start       = 0xB1,
  cfg_main        = 0xB2,
  cfg_civ_address = 0xB3,
  cfg_civ_speed   = 0xB4,
  cfg_civ_ic735   = 0xB5,
  cfg_map_band    = 0xB6,
  cfg_map_ant     = 0xB7,
  cfg_ant_sel     = 0xB8,
  cfg_ant_name    = 0xB9,
  cfg_info        = 0xBA,
  cfg_factory     = 0xBB,
  cfg_exit        = 0xBF
};

// CI-V serial speed
enum serial_speed_t : uint8_t {
  disable   = 0x00,
  bps_1200  = 0x01,
  bps_2400  = 0x02,
  bps_4800  = 0x03,
  bps_9600  = 0x04,
  bps_19200 = 0x05
};

// Enum for button status
enum key_status_t : uint8_t {
  key_none      = 0x20,
  key_up        = 0x21,
  key_down      = 0x22,
  key_menu      = 0x23,
  key_menu_long = 0x24,
  key_esc       = 0x25

};

enum action_t : uint8_t {
  action_save   = 0x41,
  action_cancel = 0x42,
  action_none =   0x43
};

/* ----------------------------------------------------------------------------------------------------------------
 *                                               STRUCTs
 * ----------------------------------------------------------------------------------------------------------------
*/

struct network_t {
  uint8_t     ip[4]   = {0,0,0,0};      // Static or failback IP Address
  uint8_t     mask[4] = {0,0,0,0};      // Static or failback subnet mask
  uint8_t     gw[4]   = {0,0,0,0};      // Static or failback gateway
  uint8_t     mac[6]  = {0,0,0,0};      // Device mac address (computer on startup)
  dhcp_status_t  dhcp = dynamic;        // Track how the address was assigned
  uint16_t dhcp_timer = 0 ;             // DHCP Timer for rebind/renew
};

// Structure for controller configuration

//struct settings_t {                                  /*  Description                     */
                                                     /* -------------------------------- */
//  uint16_t     checksum = 0;                         /* configuration checksum           */
//  serial_speed_t serial = disable;                   /* Serial port speed                */
//  boolean     ic735mode = false;                     /* CI-V 735 mode                    */
//  uint8_t       address = 0x00;                      /* CI-V transceiver address         */
//  uint8_t band_antenna[HAM_BANDS +1];                /* 1:1 Array for the band<>antenna  */
//  char ant_names[ANT_COUNT*ANT_NAME_LEN+1];          /* Array for antenna names          */
//};


// Structure holding all information about current controller state
struct operate_status_t {                            /*  Description                     */
                                                     /* -------------------------------- */
  operate_states_t     state = oper_auto;            /*  current controller state        */
  uint32_t              freq = 0;                    /*  current frequency               */
  uint8_t           band_idx = 0;                    /*  pointer to hambands const       */
  uint8_t        antenna_idx = 0;                    /*  currently selected antenna      */
  key_status_t           key = key_none;             /*  button status                   */
};


// Store configuration menu status
struct configure_status_t  {                         /*  Description                     */
                                                     /* -------------------------------- */
  configure_states_t  state = cfg_null;              /* Configuation state machine       */
  uint8_t     timeout_timer = 0;                     /* 1 sec timer for timeout eval     */
  uint8_t          main_idx = 0;                     /* Index to track first level menu  */
  uint8_t           sub_idx = 0;                     /* Index to track second level menu */
  uint8_t          char_idx = 0;                     /* Track char during name editing   */
  action_t           action = action_none;           /* Used for printing action msg     */
  key_status_t          key = key_none;              /* Button status                    */
  boolean       save_eeprom = false;                 /* true if save EEPROM is needed    */
  char    new_name[(LCD_COLS - 4)];                  /* Temp space for storing new name  */

};


// Structure defining an Ham Band
struct hamband_t {
  uint8_t  meters;
  uint32_t f_start;
  uint32_t f_end ;
};

/* ----------------------------------------------------------------------------------------------------------------
 *                                    CONSTs (BAND DEFINITION)
 * ----------------------------------------------------------------------------------------------------------------
*/

// constant array containing band definition
// Add or remove rows based on BANDS_COUNT macro defined in params.h
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

// end of define guard
#endif

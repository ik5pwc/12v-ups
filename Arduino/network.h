/* ---------------------------------------------------------------------------------------
 * File        : network.h
 * Author      : Civinini Luca - IK5PWC
 *                 luca@civinini.net - http://www.civinini.net
 *                 luca@ik5pwc.it    - http://www.ik5pwc.it
 *
 * Description : header file for controller functions
 * ---------------------------------------------------------------------------------------
*/


// Define guard for this file
#ifndef network_h
#define network_h


/* ------------ Includes ------------ */
#include <Arduino.h>              // Include arduino headers
#include "params.h"               // Include program params
#include "datatypes.h"            // Include custom data types
#include <SPI.h>
#include <Ethernet.h>
#include <MQTT.h>


/* ------------ Network Macro ------- */
#define DHCP_TIMER_SEC 600    // Seconds after renew or rebind is tried
#define REFRESH_INTERVAL 5    // After often send update data to connected clients


/* -------- Public functions --------- */
void init_network(network_t *net);
void init_mqtt();
void manage_ip(network_t *net);
void manage_network(dc_out_t *dc);
void manage_mqtt (dc_out_t *dc);


#endif /* NETWORK_H_ */

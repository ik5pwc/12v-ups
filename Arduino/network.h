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


#define DHCP_TIMER_SEC 300   // Seconds after renew or rebind is tried

/* -------- Public functions --------- */
void init_network(network_t *net);

#endif /* NETWORK_H_ */

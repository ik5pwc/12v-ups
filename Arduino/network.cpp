/* ---------------------------------------------------------------------------------------
 * File        : network.cpp
 * Author      : Civinini Luca - IK5PWC
 *                 luca@civinini.net - http://www.civinini.net
 *                 luca@ik5pwc.it    - http://www.ik5pwc.it
 *
 * Description : This file contains all network-related functions
 * ---------------------------------------------------------------------------------------
*/

// Include header file
#include "network.h"


/* ------- private global variables -------- */
static EthernetServer g_netserver = EthernetServer(PORT);
static EthernetClient g_client[4];
static void print_status(EthernetClient *clt);

/*----------------------------------------------------------------------------------------------------------------------
 * Function: init_network
 * -------------------------------
 * Initialize network operation: it tries to get IP from DHCP or use static one
 *
 * Invoked by:
 * . setup              (UPSMonitor.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used:
 *  . g_netserver       (network.cpp)
 *
 * Global variables used: NONE
 *  . static_ip         (params.h)
 *  . static_mask       (params.h)
 *  . static_gw         (params.h)
 *
 * Pre Processor Macro:
 *  . DHCP_TIMER_SEC    (network.h)
 *
 * Struct:
 *  . network_t         (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . *net: pointer to a network_t struct containing current network config
*/
void init_network(network_t *net) {

	// Copy static value as default ones
/*	memcpy(net->ip  ,static_ip  ,sizeof net->ip);
	memcpy(net->mask,static_mask,sizeof net->mask);
	memcpy(net->gw  ,static_gw  ,sizeof net->gw);
*/
	// Compute the MAC Address from static IP
	net->mac[3] = static_ip[0]; net->mac[4] = static_ip[1];
	net->mac[5] = static_ip[2]; net->mac[6] = static_ip[3];

	// Configure
	if (ENABLE_DHCP) {net->dhcp = dynamic;} else {net->dhcp = manual;}

	// try to get IP from DHCP
	if (net->dhcp == dynamic) {
		// DHCP is enabled, try to get IP address and use failback if assignment go wrong
		if (Ethernet.begin(net->mac,20000,10000) == 1) {
			net->dhcp = assigned;
		} else {
			Ethernet.begin(net->mac,static_ip,{0,0,0,0},static_gw, static_mask);
		  net->dhcp = fallback;
		}

		// Init DHCP Renew timer
		net->dhcp_timer = DHCP_TIMER_SEC;
	} else {
	  // Static IP used
    Ethernet.begin(net->mac,static_ip,{0,0,0,0},static_gw,static_mask);
	}

	// Save current IP Address
  net->ip[0] = Ethernet.localIP()[0];  net->mask[0] = Ethernet.subnetMask()[0];  net->gw[0] = Ethernet.gatewayIP()[0];
  net->ip[1] = Ethernet.localIP()[1];  net->mask[1] = Ethernet.subnetMask()[1];	 net->gw[1] = Ethernet.gatewayIP()[1];
  net->ip[2] = Ethernet.localIP()[2];  net->mask[2] = Ethernet.subnetMask()[2];  net->gw[2] = Ethernet.gatewayIP()[2];
  net->ip[3] = Ethernet.localIP()[3];  net->mask[3] = Ethernet.subnetMask()[3];  net->gw[3] = Ethernet.gatewayIP()[3];

	// Start server
	g_netserver.begin();
}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: manage_network
 * -------------------------------
 * Perform DHCP renew or reset to fallback address
 *
 * Invoked by:
 * . loop               (UPSMonitor.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used: NONE
 *  . static_ip         (params.h)
 *  . static_mask       (params.h)
 *  . static_gw         (params.h)
 *
 * Pre Processor Macro:
 *  . DHCP_TIMER_SEC    (network.h)
 *
 * Struct:
 *  . network_t         (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . *net: pointer to a network_t struct containing current network config
*/
void manage_network(network_t *net) {
  uint8_t ret = 0;    // Return value for renew or discover function

	// Update DHCP Timer
	if ( (millis() / 1000 ) % 2 == net->dhcp_timer % 2 ) { net->dhcp_timer--;}

	// Check if timer expired
	if (net->dhcp_timer == 0) {

    switch (net->dhcp) {
	    case assigned:
	    	// IP was previously assigned, try renew
	    	ret = Ethernet.maintain();

	    	// If renew fails, go fallback
	    	if (ret == 1 || ret == 3) {
	    		Ethernet.begin(net->mac,static_ip,{0,0,0,0},static_gw, static_mask);
	    		net->dhcp = fallback;
	    	}
	    	break;

	    case fallback:
	    	// Fallback IP was in use, try to get one from dhcp
	    	ret = Ethernet.begin(net->mac,20000,10000);

	    	if (ret == 0) {
	    		// DHCP still unavailable reset ti fallback
	    		Ethernet.begin(net->mac,static_ip,{0,0,0,0},static_gw, static_mask);
	    		net->dhcp = fallback;
	    	} else {
	    		// DHCP process went ok
	    		net->dhcp = assigned;
	    	}
	    	break;
	  }

	  // Save new IP config in global struct
		net->ip[0] = Ethernet.localIP()[0];  net->mask[0] = Ethernet.subnetMask()[0];  net->gw[0] = Ethernet.gatewayIP()[0];
    net->ip[1] = Ethernet.localIP()[1];  net->mask[1] = Ethernet.subnetMask()[1];	 net->gw[1] = Ethernet.gatewayIP()[1];
    net->ip[2] = Ethernet.localIP()[2];  net->mask[2] = Ethernet.subnetMask()[2];  net->gw[2] = Ethernet.gatewayIP()[2];
    net->ip[3] = Ethernet.localIP()[3];  net->mask[3] = Ethernet.subnetMask()[3];  net->gw[3] = Ethernet.gatewayIP()[3];

		// All things done, reset timer
		net->dhcp_timer = DHCP_TIMER_SEC;
  }
}





void manage_netserver() {
  char rx_buffer[50];                // Store data sent from client
	bool close_conn = false,        // If set to true disconnect client
			    send_status = false;       // if set to true, status data is sent

  static uint8_t timer = 0;
  uint8_t now = 0;

  // Create a client object to manage data from client (if any)
	EthernetClient telnet_client = g_netserver.available();

	// Is there any client request waiting to be served ?
	if (telnet_client) {

		// read data from client
		for (uint8_t i=0; i < sizeof(rx_buffer) && i < telnet_client.available(); i++) {
			rx_buffer[i]=telnet_client.read();

			// if X char was receive, set disconnect flag
			if (rx_buffer[i] == 0x78 || rx_buffer[i] == 0x58) {close_conn = true;}
		}

		// Execute disconnect
		if (close_conn) {telnet_client.stop();}
	}

	now = millis()/5000 % 2;
	if (now != timer) {

		timer = now;
    g_netserver.write(0x1b);g_netserver.write("[2J");
    g_netserver.write(0x1b);g_netserver.write("[1;1H");
  	g_netserver.println ("DC UPSMonitor");
	  g_netserver.println ("-------------\n");
	  g_netserver.println ("Status: AC Input");
	  g_netserver.println ("Vout  : XX.YY V\n");
	  g_netserver.println ("Module 1          Module 2          Module 3");
	  g_netserver.println ("---------------+-----------------+---------------");
	  g_netserver.println ("Iout: 00.00 A  |  Iout: 00.00 A  |  Iout: 00.00 A");
	  g_netserver.println ("Ibat: 00.00 A  |  Ibat: 00.00 A  |  Ibat: 00.00 A");
	  g_netserver.println ("Vbat: 00.00 V  |  Vbat: 00.00 V  |  Vbat: 00.00 V");
	  g_netserver.println ("---------------+-----------------+---------------");
	  g_netserver.println ("\nPress X to disconnect");
  }


	//if (client == 1) { Serial.println("rucevi"); Serial.println(client.read());}
	// Serial.println("rucevi"); Serial.println(client.read());
}

void print_status(EthernetClient *clt) {
  clt->write(0x1b);clt->write("[2J");
  clt->write(0x1b);clt->write("[1;1H");
  clt->println ("DC UPSMonitor");
  clt->println ("-------------\n");
  clt->println ("Status: AC Input");
  clt->println ("Vout  : XX.YY V\n");
  clt->println ("Module 1          Module 2          Module 3");
  clt->println ("---------------+-----------------+---------------");
  clt->println ("Iout: 00.00 A  |  Iout: 00.00 A  |  Iout: 00.00 A");
  clt->println ("Ibat: 00.00 A  |  Ibat: 00.00 A  |  Ibat: 00.00 A");
  clt->println ("Vbat: 00.00 V  |  Vbat: 00.00 V  |  Vbat: 00.00 V");
  clt->println ("---------------+-----------------+---------------");
  clt->println ("\nPress X to disconnect");
}
/*
Stream ooo(EthernetClient *clt) {
	char* message;
	Stream char d;


  d.write(0x1b);d.write("[2J");
  d.write(0x1b);d.write("[1;1H");
  d.println ("DC UPSMonitor");
  d.println ("-------------\n");
  d.println ("Status: AC Input");
  d.println ("Vout  : XX.YY V\n");
  d.println ("Module 1          Module 2          Module 3");
  d.println ("---------------+-----------------+---------------");
  d.println ("Iout: 00.00 A  |  Iout: 00.00 A  |  Iout: 00.00 A");
  d.println ("Ibat: 00.00 A  |  Ibat: 00.00 A  |  Ibat: 00.00 A");
  d.println ("Vbat: 00.00 V  |  Vbat: 00.00 V  |  Vbat: 00.00 V");
  d.println ("---------------+-----------------+---------------");
  d.println ("\nPress X to disconnect");

  return d;
}
*/

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


void init_network(network_t *net) {

	// Copy static value as default ones
	memcpy(net->ip  ,static_ip  ,sizeof net->ip);
	memcpy(net->mask,static_mask,sizeof net->mask);
	memcpy(net->gw  ,static_gw  ,sizeof net->gw);

	// Compute the MAC Address from static IP
	net->mac[3] = net->ip[0]; net->mac[4] = net->ip[1];
	net->mac[5] = net->ip[2]; net->mac[6] = net->ip[3];

	// try to get IP from DHCP
	if (net->dhcp) {
		// DHCP is enabled, try to get IP address
		if (Ethernet.begin(net->mac) == 1) {

			// IP Address assigned, save in array
			net->ip[0] = Ethernet.localIP()[0];  net->mask[0] = Ethernet.subnetMask()[0];  net->gw[0] = Ethernet.gatewayIP()[0];
      net->ip[1] = Ethernet.localIP()[1];  net->mask[1] = Ethernet.subnetMask()[1];	 net->gw[1] = Ethernet.gatewayIP()[1];
      net->ip[2] = Ethernet.localIP()[2];  net->mask[2] = Ethernet.subnetMask()[2];  net->gw[2] = Ethernet.gatewayIP()[2];
      net->ip[3] = Ethernet.localIP()[3];  net->mask[3] = Ethernet.subnetMask()[3];  net->gw[3] = Ethernet.gatewayIP()[3];

		} else {
		  // DHCP Failed, use static IP
      Ethernet.begin(net->mac,net->ip,{0,0,0,0},net->gw,net->mask);
		}

    // Init DHCP Renew timer
		net->dhcp_timer = DHCP_TIMER_SEC;
	} else {
	  // Static IP used
    Ethernet.begin(net->mac,net->ip,{0,0,0,0},net->gw,net->mask);
	}
}

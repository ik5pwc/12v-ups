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
static EthernetServer g_netserver = EthernetServer(PORT);     // Ethernet telnet server
static EthernetClient g_netclient;                            // Ethernet Client
static char g_reply[50];                                      // Telnet reply
static MQTTClient g_mqtt_publisher;                           // MQTT client for publisher


/* ---- Static functions (i.e. callable only within this file) ----- */
void build_reply(dc_out_t *dc, uint8_t row);



/*----------------------------------------------------------------------------------------------------------------------
 * Function: manage_mqtt
 * -------------------------------
 * Send data to mqtt broker
 *
 * Invoked by:
 * . loop               (UPSMonitor.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 *  . g_mqtt_publisher  (network.cpp)
 *
 * Pre Processor Macro:
 * . MQTTCLIENTID       (params.h)
 * . MQTTTOPIC          (params.h)
 *
 * Struct:
 *  . dc_out_t          (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . *dc: pointer to adc_out_t struct containing electric measures
*/
void manage_mqtt(dc_out_t *dc) {
  char value[7];               // For converting float to string
  char topic[50];               // Topic name

	// If broker is not connected, try reconnecting
	if (! g_mqtt_publisher.connected() ){ g_mqtt_publisher.connect(MQTTCLIENTID); }

  // If connected and time expired, publish data
	if (g_mqtt_publisher.connected()) {

    // UPS status
		strcpy(topic,MQTTTOPIC);strcat(topic,"/status");
		if (dc->ps_vout > 5 ) { g_mqtt_publisher.publish(topic,F("AC Power"));} else {g_mqtt_publisher.publish(topic,F("Battery"));}

		// UPS Vout
		dtostrf(dc->ups_vout, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/out/volt");
		g_mqtt_publisher.publish(topic,value);

    // UPS Iout
		dtostrf(dc->ups_itot, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/out/amp");
		g_mqtt_publisher.publish(topic,value);

    // Load Power
		dtostrf(dc->ups_pwr, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/out/watt");
		g_mqtt_publisher.publish(topic,value);

    // Module 1 out current
		dtostrf(dc->m1_iout, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m1/out/amp");
		g_mqtt_publisher.publish(topic,value);

    // Module 1 Battery Voltage
		dtostrf(dc->m1_vbat, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m1/bat/volt");
		g_mqtt_publisher.publish(topic,value);

    // Module 1 Battery Current
		dtostrf(dc->m1_vbat, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m1/bat/amp");
		g_mqtt_publisher.publish(topic,value);

    // Module 2 out current
		dtostrf(dc->m2_iout, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m2/out/amp");
		g_mqtt_publisher.publish(topic,value);

    // Module 2 Battery Voltage
		dtostrf(dc->m2_vbat, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m2/bat/volt");
		g_mqtt_publisher.publish(topic,value);

    // Module 2 Battery Current
		dtostrf(dc->m2_vbat, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m2/bat/amp");
		g_mqtt_publisher.publish(topic,value);

    // Module 3 out current
		dtostrf(dc->m3_iout, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m3/out/amp");
		g_mqtt_publisher.publish(topic,value);

    // Module 3 Battery Voltage
		dtostrf(dc->m3_vbat, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m3/bat/volt");
		g_mqtt_publisher.publish(topic,value);

    // Module 3 Battery Current
		dtostrf(dc->m3_vbat, 4, 2, value);
  	strcpy(topic,MQTTTOPIC);strcat(topic,"/m3/bat/amp");
		g_mqtt_publisher.publish(topic,value);
  }
}


/*----------------------------------------------------------------------------------------------------------------------
 * Function: init_mqtt
 * -------------------------------
 * Initialize MQTT operation.
 *
 * Invoked by:
 * . setup              (UPSMonitor.ino)
 *
 * Called Sub/Functions: NONE
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 *  . g_mqtt_publisher  (network.cpp)
 *
 * Pre Processor Macro:
 *  . MQTTBROKER        (params.h)
 *  . MQTTPORT          (params.h)
 *
 * Struct: NONE
 *
 * Enum: NONE
 *
 * Arguments: NONE
*/
void init_mqtt() {
	// Configure the broker (IP hard-coded in the software)
	g_mqtt_publisher.begin(MQTTBROKER,MQTTPORT,g_netclient);
}



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
 * Global Const Used: NONE
 *
 * Global variables used:
 *  . g_netserver       (network.cpp)
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
	// Compute the MAC Address from static IP
	net->mac[3] = static_ip[0]; net->mac[4] = static_ip[1];
	net->mac[5] = static_ip[2]; net->mac[6] = static_ip[3];

	// Configure DHCP or static
	if (ENABLE_DHCP) {net->dhcp = dynamic;} else {net->dhcp = manual;}

	// try to get IP from DHCP
	if (net->dhcp == dynamic) {
		// DHCP is enabled, try to get IP address and use failback if assignment go wrong
		if (Ethernet.begin(net->mac,20000,10000) == 1) {
			net->dhcp = assigned;
			D_print("DHCP "); D_print (Ethernet.localIP());
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
	//g_netserver.begin();
}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: manage_ip
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
 * Global variables used:
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
void manage_ip(network_t *net) {
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



/*----------------------------------------------------------------------------------------------------------------------
 * Function: manage_network
 * -------------------------------
 * Send data to connected clients
 *
 * Invoked by:
 * . loop               (UPSMonitor.ino)
 *
 * Called Sub/Functions:
 * . build_reply        (network.cpp)
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 *  . g_netserver       (network.cpp)
 *  . g_reply           (network.cpp)
 *
 * Pre Processor Macro:
 * . REFRESH_INTERVAL   (network.h)
 *
 * Struct:
 *  . network_t         (datatypes.h)
 *  . dc_out_t          (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . *dc: pointer to adc_out_t struct containing electric measures
*/

void manage_network(dc_out_t* dc, bool update) {
  char rx_buffer[10];                           // Buffer for data sent by client
  bool close_conn = false;                      // If set to true disconnect client

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

		// Send data to client
		for (uint8_t i=0; i<=6;i++) {build_reply(dc,i);	telnet_client.write(g_reply);}
	}

	// If timer expired, send data and reset timer
	if (update) {
		for (uint8_t i=0; i<=6;i++) {build_reply(dc,i);	g_netserver.write(g_reply);}
  }
}



/*----------------------------------------------------------------------------------------------------------------------
 * Function: build_reply
 * -------------------------------
 * Build reply message for clients
 *
 * Invoked by:
 * . manage_netserver   (network.cpp)
 *
 * Called Sub/Functions:
 * . append             (network.cpp)
 *
 * Global Const Used: NONE
 *
 * Global variables used:
 *  . g_reply           (network.cpp)
 *
 * Pre Processor Macro: NONE
 *
 * Struct:
 * . dc_out_t           (datatypes.h)
 *
 * Enum: NONE
 *
 * Arguments:
 * . *dc: pointer to adc_out_t struct containing electric measures
*/
void build_reply(dc_out_t *dc, uint8_t row) {
  char value[7];         // For converting float to string

	// Cleanup reply buffer
	for (uint16_t i = 0; i < sizeof(g_reply); i++) {g_reply[i]=0x20;}
  switch (row) {
    case 0:
  		strcpy(g_reply,"|[?25l|[2J|[1;1H");   // Telnet commands to:
					                                  // [?25l --> Disable cursor blinking
			    																	// [2J   --> Clear screen
			                                      // [1;1H --> Set cursor to position 1,1
					                                  // | is the escape char (0x1B) which is not printable
  		// Now replace | with escape char 0X1B
      for (uint16_t i = 0; i < sizeof(g_reply); i++) { if (g_reply[i] == 0x7C ) {g_reply[i] = 0x1b;}}
      strcat(g_reply,"DC UPSMonitor\n\n");
      break;

    case 1: // out status
    	if (dc->ps_vout > 5 ) {strcpy(g_reply,"AC Input\n");} else {strcpy(g_reply,"Battery\n");}
      strcat(g_reply, "Out -> ");
      dtostrf(dc->ups_vout, 4, 2, value);
      strcat(g_reply,value);
      strcat(g_reply,"V  ");
      dtostrf(dc->ups_itot, 4, 2, value);
      strcat(g_reply,value);
      break;

    case 2:
      strcpy(g_reply,"A ");
      dtostrf(dc->ups_pwr, 4, 2, value);
      strcat(g_reply,value);
      strcat(g_reply,"W\n\n");
    	break;

    case 3:
      strcpy(g_reply,"M1 -> ");
      strcat(g_reply,"Iout:");  dtostrf(dc->m1_iout, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "A ");
      strcat(g_reply,"Ibat:");  dtostrf(dc->m1_ibat, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "A ");
      strcat(g_reply,"Vbat:");  dtostrf(dc->m1_vbat, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "V\n");
      break;

    case 4:
      strcpy(g_reply,"M2 -> ");
      strcat(g_reply,"Iout:");  dtostrf(dc->m2_iout, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "A ");
      strcat(g_reply,"Ibat:");  dtostrf(dc->m2_ibat, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "A ");
      strcat(g_reply,"Vbat:");  dtostrf(dc->m2_vbat, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "V\n");
      break;

    case 5:
      strcpy(g_reply,"M3 -> ");
      strcat(g_reply,"Iout:");  dtostrf(dc->m3_iout, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "A ");
      strcat(g_reply,"Ibat:");  dtostrf(dc->m3_ibat, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "A ");
      strcat(g_reply,"Vbat:");  dtostrf(dc->m3_vbat, 4, 2, value); strcat(g_reply,value); strcat(g_reply, "V\n");
      break;

    case 6:
    	strcpy(g_reply,"\nX to exit\n");
    	break;
  }
}


/*
   ---------------------------------------------------------------------------------------
   File        : UPSMonitor.ino
   Author      : IK5PWC, Civinini Luca - luca@ik5pwc.it - http://www.ik5pwc.it
   Created     : 2011/09/20
   Description : This is the main file. Purpose of his sketch/project is to monitor a DC ups
                 and report status via ethernet

   Licensed freely only to authorized amateur radio stations. Any other use is forbidden.
   Use this code at your own risk.
   Code can be modified and redistributed under following  conditions:
   1) You should not remove any reference to original author
   2) Your changes must be forwarded to original  author
   3) Any commercial activity is forbidden

   ---------------------------------------------------------------------------------------
*/

/* -------------- Include files (project specific) ------------- */
#include <Arduino.h>
#include "params.h"
#include "network.h"
#include "lcd.h"
#include "io.h"


//TODO: mettere le letture potenza in telnet
//TODO: mettere lo stato del MQTT (connesso)


/* ------------------------------- GLOBAL VARIABLES DECLATATION ---------------------------- */
static struct network_t  g_netstatus;   // Define globally network status


//The setup function is called once at startup of the sketch
void setup(){
  // Debugging
  Serial.println(9600);

  // Init LCD
  lcd_init();

  // Ethernet init
	init_network(&g_netstatus);

	// Init mqtt support (if enabled)
	if (MQTTSUPPORT) {init_mqtt();}
}

// The loop function is called in an endless loop
void loop(){
	static struct dc_out_t  dcstatus;         // hold sensor readings
	static key_status_t     button = off;     // hold buttons

	// If dynamic address is in use, renew or try to get a new one
	if (g_netstatus.dhcp) {manage_ip(&g_netstatus);}

  // Read DC data
	read_sensor (&dcstatus);

	// Read buttons
	button = read_keys_analog();

	// Update display
	lcd_operate(&dcstatus, &g_netstatus, &button);

	// Manage telnet clients
	manage_network(&dcstatus);

  // if enabled, manage MQTT connection
	if (MQTTSUPPORT) {manage_mqtt( &dcstatus);}
}

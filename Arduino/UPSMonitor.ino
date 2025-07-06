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
#include "Arduino.h"
#include "params.h"
#include "network.h"




/* ------------------------------- GLOBAL VARIABLES DECLATATION ---------------------------- */
static struct network_t  g_netstatus;   // Define globally network status



//The setup function is called once at startup of the sketch
void setup(){
  // Debugging
  Serial.begin(9600);

  // Ethernet init
	init_network(&g_netstatus);

	//Ethernet.begin(mac);

// Add your initialization code here
}

// The loop function is called in an endless loop
void loop(){
Serial.print(g_netstatus.ip[0]);Serial.print(".");
Serial.print(g_netstatus.ip[1]); Serial.print(".");
Serial.print(g_netstatus.ip[2]); Serial.print(".");
Serial.println(g_netstatus.ip[3]);

//	 Ethernet.maintain();

	//Serial.println(Ethernet.localIP());
	//Add your repeated code here
}

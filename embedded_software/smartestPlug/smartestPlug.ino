/*
* Author     : Cevat Bostancioglu
* Date       : 28 AUG 2016
* MCU        : ESP8266WiFi
* Purpose    : Make smartplugs more affordable for everyone. 
* Note       : Works with io.adafruit
* Connection : Over Wifi w/ SSID-PASSWORD or just press modem WPS Button
* E-mail/Loc : bostancioglucevat@gmail.com , Turkey/Ankara
*/

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "smartestPlug.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SUPERONLINE_WiFi_5109"
#define WLAN_PASS       "NUTHN9ULWTVY"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "cevatbostancioglu"
#define AIO_KEY         "07ced671cb34ffb78bc673d149c321c67a7bd947"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe plugState = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/homePlug0");

void MQTT_connect();

SmartestPlug netPlug(&mqtt,&plugState,1);

void setup() {
  
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  netPlug.Connect();
  netPlug.newRule("ON",1,1);
  netPlug.newRule("OFF",1,0);
  // netPlug.newRule("ON",netPlug.openPlug);
  // netPlug.newRule("OFF",netPlug.closePlug);
  
}

void loop() 
{
	
	
  netPlug.Read_Updates();
  delay(1);
}



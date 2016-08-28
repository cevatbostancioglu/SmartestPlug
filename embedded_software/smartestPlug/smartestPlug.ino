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

#define WLAN_SSID       "**YourWifiSSID**"
#define WLAN_PASS       "**YourWifiPass**"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "**Adafruit_User_name**"
#define AIO_KEY         "**Adafruit_key**"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
// Setup a feed called 'onoff' for subscribing to changes.

Adafruit_MQTT_Subscribe plugState0 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/homePlug0");

Adafruit_MQTT_Subscribe plugState1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/homePlug1");

Adafruit_MQTT_Subscribe plugState2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/homePlug2");

Adafruit_MQTT_Subscribe plugState3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/homePlug3");

Adafruit_MQTT_Subscribe plugState4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/homePlug4");

SmartestPlug netPlug(&mqtt,&plugState0,1);

netPlug.newSubscription(&plugState1);
netPlug.newSubscription(&plugState2);
netPlug.newSubscription(&plugState3);
netPlug.newSubscription(&plugState4);

netPlug.newRule(&plugState0,"ON",0,1);
netPlug.newRule(&plugState0,"OFF",0,0);

netPlug.newRule(&plugState1,"ON",1,1);
netPlug.newRule(&plugState1,"OFF",1,0);

netPlug.newRule(&plugState2,"ON",2,1);
netPlug.newRule(&plugState2,"OFF",2,0);

netPlug.newRule(&plugState3,"ON",3,1);
netPlug.newRule(&plugState3,"OFF",3,0);

netPlug.newRule(&plugState4,"ON",4,1);
netPlug.newRule(&plugState4,"OFF",4,0);

void setup() {

	Serial.begin(115200);
	delay(10);

	// Connect to WiFi access point.
	Serial.println(); Serial.println();
	Serial.print("Connecting to ");
	Serial.println(WLAN_SSID);

	WiFi.begin(WLAN_SSID, WLAN_PASS);
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println();

	Serial.println("WiFi connected");
	Serial.println("IP address: "); Serial.println(WiFi.localIP());

	netPlug.Connect();

}

void loop() 
{
	
	
	netPlug.Read_Updates();
	delay(1);
}



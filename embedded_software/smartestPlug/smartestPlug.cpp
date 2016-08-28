/*
* Author     : Cevat Bostancioglu
* Date       : 28 AUG 2016
* MCU        : ESP8266WiFi
* Purpose    : Make smartplugs more affordable for everyone. 
* Note       : Works with io.adafruit
* Connection : Over Wifi w/ SSID-PASSWORD or just press modem WPS Button
* E-mail/Loc : bostancioglucevat@gmail.com , Turkey/Ankara
*/
#include "smartestPlug.h"

SmartestPlug::SmartestPlug(Adafruit_MQTT_Client* _mqtt,Adafruit_MQTT_Subscribe* _subscription,int _pinRelay)
{
	subscriptionNumber=0;
	ruleNumber=0;
	
	mqtt=_mqtt;
	pinRelay = _pinRelay;
	subscription[subscriptionNumber++]=_subscription;	
}

void SmartestPlug::newSubscription(Adafruit_MQTT_Subscribe* _subscription)
{
	subscription[subscriptionNumber++]=_subscription;
}

void SmartestPlug::newRule(Adafruit_MQTT_Subscribe* _subscription,char* pRule,	int plugNumber,int value)
{
	mqttRules[ruleNumber].subscription = _subscription;
	strcpy(mqttRules[ruleNumber].ruleString,pRule);
	mqttRules[ruleNumber].plugNumber=plugNumber;
	mqttRules[ruleNumber].value=value;
	ruleNumber++;
}

void SmartestPlug::checkRule(Adafruit_MQTT_Subscribe* _subscription,char *pRuleString)
{
	for(int i=0;i<ruleNumber;i++)
	{
		if(strstr(pRuleString,mqttRules[i].ruleString) && _subscription==mqttRules[i].subscription)
		{
			if(mqttRules[i].value==1)
			{openPlug(mqttRules[i].plugNumber);}
			else if(mqttRules[i].value==0)
			{closePlug(mqttRules[i].plugNumber);}
		}
	}
}

void SmartestPlug::openPlug(int pNumber)
{
	Serial.print("**Open_");
	Serial.println(pNumber);
}

void SmartestPlug::closePlug(int pNumber)
{
	Serial.print("**Close_");
	Serial.println(pNumber);	
}

void SmartestPlug::writeMQTT()
{
	
}

void SmartestPlug::Read_Updates()
{
	readMQTT();
}

void SmartestPlug::Write_Updates()
{
	
}

void SmartestPlug::Connect()
{
	MQTT_INIT();
	MQTT_Connect();
}


void SmartestPlug::MQTT_INIT()
{
	// // Setup MQTT subscription for onoff feed.
	for(int i=0;i<subscriptionNumber;i++)
	{mqtt->subscribe(subscription[i]);}
}

void SmartestPlug::readMQTT()
{
	// Ensure the connection to the MQTT server is alive (this will make the first
	// connection and automatically reconnect when disconnected).  See the MQTT_connect
	// function definition further below.
	Adafruit_MQTT_Subscribe *_subscription;
	while ((_subscription = mqtt->readSubscription(5000))) 
	{
		for(int i=0;i<subscriptionNumber;i++)
		{
			if(_subscription == subscription[i])
			{
				if(debugOverSerial)
				{
					Serial.print(F("Got: "));
					Serial.println((char *)subscription[i]->lastread);
				}
				
				checkRule(subscription[i],(char*)subscription[i]->lastread);
			}
		}
	}
}



void SmartestPlug::printHex(byte *buffer, byte bufferSize) 
{
	for (byte i = 0; i < bufferSize; i++) 
	{
		Serial.print(buffer[i] < 0x10 ? " 0" : " ");
		Serial.print(buffer[i], HEX);
	}
}

/**
* Helper routine to dump a byte array as dec values to Serial.
*/
void SmartestPlug::printDec(byte *buffer, byte bufferSize) {
	for (byte i = 0; i < bufferSize; i++) {
		Serial.print(buffer[i] < 0x10 ? " 0" : " ");
		Serial.print(buffer[i], DEC);
	}
}

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void SmartestPlug::MQTT_Connect() {
	
	int8_t ret;

	// Stop if already connected.
	if (mqtt->connected()) {
		return;
	}
	
	if(debugOverSerial)
	{Serial.print("Connecting to MQTT... ");}

	uint8_t retries = 3;
	while ((ret = mqtt->connect()) != 0) { // connect will return 0 for connected
		if(debugOverSerial)
		{
			Serial.println(mqtt->connectErrorString(ret));
			Serial.println("Retrying MQTT connection in 3 seconds...");
		}
		
		mqtt->disconnect();
		delay(3000);  // wait 3 seconds
		retries--;
		if (retries == 0) {
			// basically die and wait for WDT to reset me
			while (1);
		}
	}
	
	if(debugOverSerial)
	{Serial.println("MQTT Connected!");}

	//mqttWriter.attach(5,writeMQTT);
}

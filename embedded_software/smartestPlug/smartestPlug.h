#ifndef SMARTEST_PLUG_H
#define SMARTEST_PLUG_H

#include <ESP8266wifi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define totalPlugNumber  1

typedef struct
{	
	char ruleString[10];
	int plugNumber;
	int value;
}mqttRule;

class SmartestPlug
{
	
public:
	
	int pinRelay;
	int debugOverSerial=1;
	
	int subscriptionNumber;
	int ruleNumber;
	
	mqttRule mqttRules[10];
	
	Adafruit_MQTT_Client *mqtt;
	Adafruit_MQTT_Subscribe *subscription[30];
	SmartestPlug(Adafruit_MQTT_Client* _mqtt,Adafruit_MQTT_Subscribe* _subscription,int _pinRelay);
	
	void newSubscription(Adafruit_MQTT_Subscribe* _subscription);
	void newRule(char* pRule,int plugNumber,int value);
	void checkRule(char *pRuleString);
	
	void Read_Updates();
	void Write_Updates();
	void Connect();
	void openPlug(int pNumber);
	void closePlug(int pNumber);
private:
	void writeMQTT();
	void readMQTT();
	void MQTT_INIT();
	void printHex(byte *buffer, byte bufferSize);
	void printDec(byte *buffer, byte bufferSize);
	void MQTT_Connect();
	
};

#endif




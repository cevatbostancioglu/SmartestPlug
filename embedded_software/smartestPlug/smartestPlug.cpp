// #include "smartestPlug.h"

// SmartestPlug::SmartestPlug(Adafruit_MQTT_Client* _mqtt,Adafruit_MQTT_Subscribe* _subscription,int _pinRelay)
// {
	// mqtt=_mqtt;
	// pinRelay = _pinRelay;
	// subscription=_subscription;	
// }

// void SmartestPlug::openPlug()
// {
	// Serial.println("Acildi.");
// }

// void SmartestPlug::closePlug()
// {
	// Serial.println("Kapatildi.");
// }

// void SmartestPlug::writeMQTT()
// {
	
// }

// void SmartestPlug::Read_Updates();

// void SmartestPlug::Write_Updates();

// void SmartestPlug::Connect()
// {
	// MQTT_INIT();
	// MQTT_Connect();
// }


// void SmartestPlug::MQTT_INIT()
// {
	// if(debugOverSerial)
	// {
		// Serial.println(); Serial.println();
		// Serial.print("Connecting to ");
		// Serial.println(WLAN_SSID);
	// }
	
	// WiFi.begin(WLAN_SSID, WLAN_PASS);

	// while (WiFi.status() != WL_CONNECTED) 
	// {
		// delay(500);
		
		// if(debugOverSerial)
		// {Serial.print(".");}
	// }
	
	// if(debugOverSerial)
	// {
		// Serial.println();
		// Serial.println("WiFi connected");
		// Serial.println("IP address: "); 
		// Serial.println(WiFi.localIP());
	// }
	// // Setup MQTT subscription for onoff feed.
	// mqtt.subscribe(&subscription);
// }

// void SmartestPlug::readMQTT()
// {
	// // Ensure the connection to the MQTT server is alive (this will make the first
	// // connection and automatically reconnect when disconnected).  See the MQTT_connect
	// // function definition further below.
	// Adafruit_MQTT_Subscribe *_subscription;
	// while ((_subscription = mqtt.readSubscription(5000))) 
	// {
		// if (_subscription == &subscription) 
		// {
			// Serial.print(F("Got: "));
			// Serial.println((char *)subscription.lastread);
			
			// if(strstr((char*)subscription.lastread,"1"))
			// {openDoor();}
		// }
	// }
// }



// void SmartestPlug::printHex(byte *buffer, byte bufferSize) 
// {
	// for (byte i = 0; i < bufferSize; i++) 
	// {
		// Serial.print(buffer[i] < 0x10 ? " 0" : " ");
		// Serial.print(buffer[i], HEX);
	// }
// }

// /**
// * Helper routine to dump a byte array as dec values to Serial.
// */
// void SmartestPlug::printDec(byte *buffer, byte bufferSize) {
	// for (byte i = 0; i < bufferSize; i++) {
		// Serial.print(buffer[i] < 0x10 ? " 0" : " ");
		// Serial.print(buffer[i], DEC);
	// }
// }

// // Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// // for some reason (only affects ESP8266, likely an arduino-builder bug).
// // Function to connect and reconnect as necessary to the MQTT server.
// // Should be called in the loop function and it will take care if connecting.
// void SmartestPlug::MQTT_Connect() {
	
	// int8_t ret;

	// // Stop if already connected.
	// if (mqtt.connected()) {
		// return;
	// }
	
	// if(debugOverSerial)
	// {Serial.print("Connecting to MQTT... ");}

	// uint8_t retries = 3;
	// while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
		// if(debugOverSerial)
		// {
			// Serial.println(mqtt.connectErrorString(ret));
			// Serial.println("Retrying MQTT connection in 3 seconds...");
		// }
		
		// mqtt.disconnect();
		// delay(3000);  // wait 3 seconds
		// retries--;
		// if (retries == 0) {
			// // basically die and wait for WDT to reset me
			// while (1);
		// }
	// }
	
	// if(debugOverSerial)
	// {Serial.println("MQTT Connected!");}

	// //mqttWriter.attach(5,writeMQTT);
// }

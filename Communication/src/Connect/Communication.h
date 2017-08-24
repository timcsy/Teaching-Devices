#include <Arduino.h>
/*
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include "WiFiManager.h"         //https://github.com/tzapu/WiFiManager
*/
#include "WifiScanner.h"
#include <WebSocketsClient.h>

class Receiver
{
	public:
		virtual ~Receiver(){}
		virtual void onReceive(uint8_t * payload, size_t length){}
};

WebSocketsClient* __webSocketClient;
Receiver* receiver;

class Communication
{
	public:
		static void setup(String host, uint16_t port)
		{
			/*
			const char* ssid     = "FHL225";
			const char* password = "";
			// We start by connecting to a WiFi network
			Serial.print("Connecting to ");
			Serial.println(ssid);
			
			WiFi.begin(ssid, password);
			
			while (WiFi.status() != WL_CONNECTED) {
				delay(500);
				Serial.print(".");
			}
			Serial.println("WiFi connected");  
			Serial.println("IP address: ");
			Serial.println(WiFi.localIP());
			*/
			/*
			//WiFiManager
			//Local intialization. Once its business is done, there is no need to keep it around
			WiFiManager wifiManager;
			wifiManager.autoConnect("AutoConnectAP");
			Serial.println("connected...yeey :)");
			Serial.setDebugOutput(true);
			*/
			
			WifiScanner wifiScanner;
			wifiScanner.setup();
			
			__webSocketClient = new WebSocketsClient();
			__webSocketClient->begin(host, port);
			__webSocketClient->onEvent(&Communication::webSocketEvent);
		}
		static void loop()
		{
			__webSocketClient->loop();
		}
		static void send(String message)
		{
			__webSocketClient->sendTXT(message);
		}
		static void webSocketEvent(WStype_t type, uint8_t * payload, size_t length)
		{
			switch(type)
			{
				case WStype_DISCONNECTED:
					Serial.printf("[WSc] Disconnected!\n");
					break;
				case WStype_CONNECTED:
					Serial.printf("[WSc] Connected to url: %s\n",  payload);
					break;
				case WStype_TEXT:
					Serial.printf("[WSc] get text: %s\n", payload);
					receiver->onReceive(payload, length);
					break;
				case WStype_BIN:
					Serial.printf("[WSc] get binary length: %u\n", length);
					hexdump(payload, length);
					break;
			}
		}
};
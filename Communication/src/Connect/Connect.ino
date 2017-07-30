#include <Arduino.h>

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <WebSocketsClient.h>
#include <Hash.h>

WebSocketsClient webSocket;


void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            {
                Serial.printf("[WSc] Connected to url: %s\n",  payload);
                
                // send message to server when Connected
                webSocket.sendTXT("{\"1\":{\"api\":\"Web.Page:::view()\",\"args\":{}},\"cookies\":{\"current_timestamp\":\"1501349471\"}}");
            }
            break;
        case WStype_TEXT:
            Serial.printf("[WSc] get text: %s\n", payload);
            
            // send message to server
            // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary length: %u\n", length);
            hexdump(payload, length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
    }
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    
    wifiManager.autoConnect("AutoConnectAP");
    
    Serial.println("connected...yeey :)");
    
    //Serial.setDebugOutput(true);
    Serial.setDebugOutput(true);
    
    webSocket.begin("tew.tw", 8080);
    //webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    // put your main code here, to run repeatedly:
    webSocket.loop();
}

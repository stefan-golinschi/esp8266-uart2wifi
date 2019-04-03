//******************************************************************************
// WiFiUartTransparentBridge
// Version 1.1.0
// Note
// This sketch is based on "WiFiTelnetToSerial - Example Transparent UART to Telnet Server for esp8266"
//******************************************************************************

#include <ESP8266WiFi.h>
#include "config.h"

WiFiServer localServer(networkport);
WiFiClient localClient;

IPAddress local_IP(10,10,10,1);
IPAddress gateway(10,10,10,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(baudrate, SERIAL_8N1);
  
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password, channel, hidden, max_connection);

  Serial.swap();
  
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if(i == 21){
    Serial.print("Could not connect to"); Serial.println(ssid);
    while(1) delay(500);
  }
  
  //start UART and the server
  localServer.begin();
  localServer.setNoDelay(true);

  Serial.print("Ready! Use 'Uart-WiFi Bridge ");
  Serial.print(WiFi.localIP());
  Serial.println(" to connect");

}

void loop() {
  //check if there are any new clients
  if (localServer.hasClient()){
    if (!localClient.connected()){
      if(localClient) localClient.stop();
      localClient = localServer.available();
    }
  }
      
  //check a client for data
  if (localClient && localClient.connected()){
    if(localClient.available()){
      size_t len = localClient.available();
      uint8_t sbuf[len];
      localClient.readBytes(sbuf, len);
      Serial.write(sbuf, len);      
    }
  }

  //check UART for data
  if(Serial.available()){
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    if (localClient && localClient.connected()){
      localClient.write(sbuf, len);
    }
  }
}

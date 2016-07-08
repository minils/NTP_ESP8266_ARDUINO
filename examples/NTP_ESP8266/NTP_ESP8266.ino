#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ntp.h"

// input your ssid and password here:
const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxx";

// initialize ntp service
// port and servername of an ntp pool
Ntp ntp(2390, "us.pool.ntp.org");

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("HELLO");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Starting ntp service");
  ntp.begin();  // open the udp port to listen for incoming connections
}

void loop() {
  Serial.println(ntp.updateTime()); // sends a request to the ntp server and returns a time_t unix timestamp
  delay(5000);
}

#ifndef NTP_H
#define NTP_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define UDP_TIMEOUT 1500

class Ntp
{
  public:
    Ntp(void);
    Ntp(unsigned int localPort, const char* ntpServerName);
    bool begin(void);
    time_t updateTime(void);

  private:
    unsigned long sendNTPpacket(IPAddress& address);
    
    unsigned int _localPort;
    IPAddress _timeServerIP;
    const char* _ntpServerName;
    static const int _NTP_PACKET_SIZE = 48;
    byte _packetBuffer[_NTP_PACKET_SIZE];
    WiFiUDP _udp;
};

#endif

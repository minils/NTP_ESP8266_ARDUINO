#include "ntp.h"

Ntp::Ntp(void)
{
  _localPort = 2390;
  _ntpServerName = "0.de.pool.ntp.org";
}

Ntp::Ntp(unsigned int localPort, const char* ntpServerName)
{
  _localPort = localPort;
  _ntpServerName = ntpServerName;
}

bool Ntp::begin(void)
{
  return _udp.begin(_localPort);
}

// send an NTP request to the time server at the given address
unsigned long Ntp::sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(_packetBuffer, 0, _NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  _packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  _packetBuffer[1] = 0;     // Stratum, or type of clock
  _packetBuffer[2] = 6;     // Polling Interval
  _packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  _packetBuffer[12]  = 49;
  _packetBuffer[13]  = 0x4E;
  _packetBuffer[14]  = 49;
  _packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  _udp.beginPacket(address, 123); //NTP requests are to port 123
  _udp.write(_packetBuffer, _NTP_PACKET_SIZE);
  _udp.endPacket();
}

time_t Ntp::updateTime(void)
{
  // get a random server form the pool
  WiFi.hostByName(_ntpServerName, _timeServerIP);
  sendNTPpacket(_timeServerIP);  // send a packet to the time server
  uint32_t beginWait = millis();

  // wait for UDP_TIMEOUT s max
  while (millis() - beginWait < UDP_TIMEOUT) {
    int size = _udp.parsePacket();
    if (size >= _NTP_PACKET_SIZE) {
      _udp.read(_packetBuffer, _NTP_PACKET_SIZE);
      unsigned long highWord = word(_packetBuffer[40], _packetBuffer[41]);
      unsigned long lowWord = word(_packetBuffer[42], _packetBuffer[43]);
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      const unsigned long seventyYears = 2208988800UL;
      time_t epoch = secsSince1900 - seventyYears;
      return epoch;
    }
  }
  // unable to get the time after UDP_TIMEOUT s
  return 0;
}


















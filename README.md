# Arduino NTP library for the ESP8266

Can be easily used with the Arduino Time Library mentioned below.

### Version
0.0.1

### Installation

Copy the files in the root of the repository to `~/Arduino/libraries/ntp/`.

### Usage

The library can be used as follows:

```cpp

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ntp.h"

const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxx";

// initialize ntp service
// port and servername
Ntp ntp(2390, "us.pool.ntp.org");

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ntp service");
  ntp.begin();
}

void loop() {
  Serial.println(ntp.updateTime());
  delay(5000);
}

```

### Known Issues

* none

### Links

* [Arduino Time Library](https://github.com/PaulStoffregen/Time)

License
----

MIT


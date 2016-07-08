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

```

### Methods

* `Ntp ntp(port, servername);` - Initialize the ntp service with a `servername` of an ntp pool and an udp `port` for incoming connections.
* `int ntp.begin();` - Open the udp port and listen for incoming connections. Returns 1 if successful or 0 if there are no sockest available to use.
* `time_t ntp.updateTime();` - Requests the time at a ntp server received from the pool and returns the current time as a unix timestamp. The timeout is set to 1500 ms.

To reduce the timeout you can `#define UDP_TIMEOUT 1500` after `#include "ntp.h"`.

### Known Issues

* none

### Links

* [Arduino Time Library](https://github.com/PaulStoffregen/Time)

License
----

MIT


# WiFiEsp

With an ESP8266 board, WiFiEsp library allows an Arduino board to connect to the internet.
It can serve as either a server accepting incoming connections or a client making outgoing ones.
The WiFiEsp library is very similar to the Arduino [WiFi](http://www.arduino.cc/en/Reference/WiFi) and [Ethernet](http://www.arduino.cc/en/Reference/Ethernet) libraries, and many of the function calls are the same. 

Supports ESP SDK version 1.1.1 and above (AT version 0.25 and above).

## Usage

For this modified version, the following hardware abstraction layer (HAL) requirements must be satisfied:

* A UART class in the HAL namespace with the following methods:
    - uint8_t UART::read(); // Read a byte from the UART buffer
	- uint8_t UART::write(uint8_t data) // Write a byte to the UART TX
	- uint32_t UART::write(char *str, uint32_t length) // Write 'length' bytes to UART TX
	- uint32_t UART::print(char *str) // Print a string to the UART TX
	- uint32_t UART::printf(const char *str, ...) // Write variable length formatted string to UART TX
	- uint32_t UART::println(const char *str) // Print string to UART TX and add newline at the end
	- bool UART::available() // Check whether input bytes have been received by UART RX internal buffer
	- uint32_t UART::parseInt() // Parse UART RX buffer as integer
	- bool UART::find(char *target) // Consume string input to UART RX buffer until 'target' string found
	- int8_t UART::peek() // Retrieve next byte from UART RX internal buffer without consuming it
* A delay_ms() function in the HAL namespace that delays an accurate milliseconds to be used for timing.

Some further requirements may also be found. Typically, these will mirror the Arduino framework and should be added to `hal.h`.

Namely, these additional requirements include functional equivalents to the Arduino framework's:

* "Stream.h"
* "Print.h"
* "Client.h"
* "Server.h"
* "IPAddress.h"
* "Udp.h"

## Features

- APIs compatible with standard Arduino WiFi library.
- Use AT commands of standard ESP firmware (no need to flash a custom firmware).
- Support hardware and software serial ports.
- Configurable tracing level.

## Wiring

The WiFiEsp library has been designed to work with the [ESP WiFi shield](http://www.instructables.com/id/Cheap-Arduino-WiFi-Shield-With-ESP8266/).
It is a cheap version of the Arduino WiFi shield that uses an ESP-01 module to provide networking capabilities to Arduino boards.


## Examples

- [ConnectWPA](https://github.com/bportaluri/WiFiEsp/blob/master/examples/ConnectWPA/ConnectWPA.ino) - Demonstrates how to connect to a network that is encrypted with WPA2 Personal
- [WebClient](https://github.com/bportaluri/WiFiEsp/blob/master/examples/WebClient/WebClient.ino) - Connect to a remote webserver 
- [WebClientRepeating](https://github.com/bportaluri/WiFiEsp/blob/master/examples/WebClientRepeating/WebClientRepeating.ino) - Make repeated HTTP calls to a webserver 
- [WebServer](https://github.com/bportaluri/WiFiEsp/blob/master/examples/WebServer/WebServer.ino) - Serve a webpage from the WiFi shield 
- [WebServerAP](https://github.com/bportaluri/WiFiEsp/blob/master/examples/WebServerAP/WebServerAP.ino) - Serve a webpage from the WiFi shield starting a local Access Point
- [WebServerLed](https://github.com/bportaluri/WiFiEsp/blob/master/examples/WebServerLed/WebServerLed.ino) - Turn on and off a led from a webpage
- [UdpNTPClient](https://github.com/bportaluri/WiFiEsp/blob/master/examples/UdpNTPClient/UdpNTPClient.ino) - Query a Network Time Protocol (NTP) server using UDP


## Supported APIs

Most of the standard Arduino WiFi library methods are available. Refer to the [WiFi library page](http://www.arduino.cc/en/Reference/WiFi) for more details.

### WiFiEsp class

- begin() - Not all authentication types
- disconnect() - YES
- config()
- setDNS() - NO (no AT command available)
- SSID() - YES
- BSSID() - YES
- RSSI() - YES
- encryptionType() - NO (no AT command available)
- scanNetworks() - YES
- getSocket()
- macAddress() - YES


### WiFiEspServer class

The WiFiEspServer class creates servers which can send data to and receive data from connected clients (programs running on other computers or devices).

- WiFiEspServer() - YES
- begin() - YES
- available() - YES
- write() - YES
- print() - YES
- println() - YES


### Client class

The WiFiEspClient class creates clients that can connect to servers and send and receive data.

- WiFiEspClient() - YES
- connected() - YES
- connect() - YES
- write() - YES
- print() - YES
- println() - YES
- available() - YES
- read() - YES
- flush() - YES
- stop() - YES


### WiFiEspUDP class

The UDP class enables UDP message to be sent and received.

- WiFiUDP - YES
- begin() - YES
- available() - YES
- beginPacket() - YES
- endPacket() - YES
- write() - YES
- parsePacket() - YES
- peek()
- read() - YES
- flush()
- stop()
- remoteIP() - YES
- remotePort() - YES


## Contributing

If you discover a bug or would like to propose a new feature, please open a new [issue](https://github.com/bportaluri/WiFiEsp/issues).

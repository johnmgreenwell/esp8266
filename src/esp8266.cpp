/*--------------------------------------------------------------------
This file is part of the Arduino WiFiEsp library.

The Arduino WiFiEsp library is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

The Arduino WiFiEsp library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Arduino WiFiEsp library.  If not, see
<http://www.gnu.org/licenses/>.
--------------------------------------------------------------------*/

#include "esp8266.h"

namespace PeripheralIO
{

int16_t 	ESP8266::_state[MAX_SOCK_NUM] = { NA_STATE, NA_STATE, NA_STATE, NA_STATE };
uint16_t 	ESP8266::_server_port[MAX_SOCK_NUM] = { 0, 0, 0, 0 };


uint8_t ESP8266::espMode = 0;


ESP8266::ESP8266()
{

}

void ESP8266::init(HAL::UART* espSerial)
{
    LOGINFO(F("Initializing ESP module"));
	EspDrv::wifiDriverInit(espSerial);
}



char* ESP8266::firmwareVersion()
{
	return EspDrv::getFwVersion();
}


int ESP8266::begin(const char* ssid, const char* passphrase)
{
    espMode = 1;
	if (EspDrv::wifiConnect(ssid, passphrase))
		return WL_CONNECTED;

	return WL_CONNECT_FAILED;
}


int ESP8266::beginAP(const char* ssid, uint8_t channel, const char* pwd, uint8_t enc, bool apOnly)
{
	if(apOnly)
        espMode = 2;
    else
        espMode = 3;
    
    if (EspDrv::wifiStartAP(ssid, pwd, channel, enc, espMode))
		return WL_CONNECTED;

	return WL_CONNECT_FAILED;
}

int ESP8266::beginAP(const char* ssid)
{
	return beginAP(ssid, 10, "", 0);
}

int ESP8266::beginAP(const char* ssid, uint8_t channel)
{
	return beginAP(ssid, channel, "", 0);
}


void ESP8266::config(IPAddress ip)
{
	EspDrv::config(ip);
}

void ESP8266::configAP(IPAddress ip)
{
	EspDrv::configAP(ip);
}



int ESP8266::disconnect()
{
    return EspDrv::disconnect();
}

uint8_t* ESP8266::macAddress(uint8_t* mac)
{
	// TODO we don't need _mac variable
	uint8_t* _mac = EspDrv::getMacAddress();
	memcpy(mac, _mac, WL_MAC_ADDR_LENGTH);
    return mac;
}

IPAddress ESP8266::localIP()
{
	IPAddress ret;
	if(espMode==1)
		EspDrv::getIpAddress(ret);
	else
		EspDrv::getIpAddressAP(ret);
	return ret;
}

IPAddress ESP8266::subnetMask()
{
	IPAddress mask;
	if(espMode==1)
    EspDrv::getNetmask(mask);
	return mask;
}

IPAddress ESP8266::gatewayIP()
{
	IPAddress gw;
	if(espMode==1)
		EspDrv::getGateway(gw);
	return gw;
}


char* ESP8266::SSID()
{
    return EspDrv::getCurrentSSID();
}

uint8_t* ESP8266::BSSID(uint8_t* bssid)
{
	// TODO we don't need _bssid
	uint8_t* _bssid = EspDrv::getCurrentBSSID();
	memcpy(bssid, _bssid, WL_MAC_ADDR_LENGTH);
    return bssid;
}

int32_t ESP8266::RSSI()
{
    return EspDrv::getCurrentRSSI();
}


int8_t ESP8266::scanNetworks()
{
	return EspDrv::getScanNetworks();
}

char* ESP8266::SSID(uint8_t networkItem)
{
	return EspDrv::getSSIDNetoworks(networkItem);
}

int32_t ESP8266::RSSI(uint8_t networkItem)
{
	return EspDrv::getRSSINetoworks(networkItem);
}

uint8_t ESP8266::encryptionType(uint8_t networkItem)
{
    return EspDrv::getEncTypeNetowrks(networkItem);
}


uint8_t ESP8266::status()
{
	return EspDrv::getConnectionStatus();
}



////////////////////////////////////////////////////////////////////////////
// Non standard methods
////////////////////////////////////////////////////////////////////////////

void ESP8266::reset(void)
{
	EspDrv::reset();
}


/*
void ESP8266::hardReset(void)
{
connected = false;
strcpy(ip, "");
digitalWrite(ESP8266_RST, LOW);
delay(ESP8266_HARD_RESET_DURATION);
digitalWrite(ESP8266_RST, HIGH);
delay(ESP8266_HARD_RESET_DURATION);
}
*/


bool ESP8266::ping(const char *host)
{
	return EspDrv::ping(host);
}

uint8_t ESP8266::getFreeSocket()
{
  // ESP Module assigns socket numbers in ascending order, so we will assign them in descending order
    for (int i = MAX_SOCK_NUM - 1; i >= 0; i--)
	{
      if (_state[i] == NA_STATE)
      {
          return i;
      }
    }
    return SOCK_NOT_AVAIL;
}

void ESP8266::allocateSocket(uint8_t sock)
{
  _state[sock] = sock;
}

void ESP8266::releaseSocket(uint8_t sock)
{
  _state[sock] = NA_STATE;
}

// WiFiEspClass WiFi;

}

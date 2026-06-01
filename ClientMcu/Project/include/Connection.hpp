#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "WiFi.h"

class Connection
{
public:
	Connection(void) = default;
	void begin(const char* wifi_name, const char* wifi_password, const char* ip, uint16_t port);
	void receive(float* temperature, float* humidity, float* soilMoisture, float* light);
	bool isAlive(void);
	
private:
	static float networkToFloat(uint32_t value);
	
	WiFiClient m_client;
};

#endif // CONNECTION_HPP
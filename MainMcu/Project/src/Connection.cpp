#include "../include/Connection.hpp"

void Connection::begin(const char* wifi_name, const char* wifi_password, const char* ip, uint16_t port)
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true, true);
    WiFi.persistent(false);
    delay(1000);
    WiFi.begin(wifi_name, wifi_password);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Waiting for WiFi connection");
        delay(500);
    }

    this->m_client.connect(ip, port);
}
void Connection::send(float temperature, float humidity, float soilMoisture, float light)
{
    uint32_t buffer[4];
    buffer[0] = Connection::floatToNetwork(temperature);
    buffer[1] = Connection::floatToNetwork(humidity);
    buffer[2] = Connection::floatToNetwork(soilMoisture);
    buffer[3] = Connection::floatToNetwork(light);

    const uint8_t* data = reinterpret_cast<const uint8_t*>(buffer);
    size_t size = sizeof(buffer);
    size_t totalSent = 0;
    while (totalSent < size)
    {
        int sent = this->m_client.write(data + totalSent, size - totalSent);
        if (sent <= 0)
        {
            break;
        }

        totalSent += sent;
    }
}
bool Connection::isAlive(void)
{
	return WiFi.status() == WL_CONNECTED && this->m_client.connected();
}

uint32_t Connection::floatToNetwork(float value)
{
	uint32_t temp;
    memcpy(&temp, &value, sizeof(value));
    return htonl(temp);
}
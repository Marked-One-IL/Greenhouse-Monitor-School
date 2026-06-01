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
void Connection::receive(float* temperature, float* humidity, float* soilMoisture, float* light)
{
    if (!temperature || !humidity || !soilMoisture || !light) return; 

    uint32_t buffer[4] = {0};
    uint8_t* data = reinterpret_cast<uint8_t*>(buffer);
    size_t size = sizeof(buffer);
    size_t totalReceived = 0;

    unsigned long startTimeout = millis();
    const unsigned long timeoutMs = 2000;

    while (totalReceived < size)
    {
        if (!this->m_client.connected()) 
        {
            Serial.println("Debug: Connection dropped during read.");
            return;
        }

        int availableBytes = this->m_client.available();
        if (availableBytes > 0)
        {
            int toRead = min((size_t)availableBytes, size - totalReceived);
            int received = this->m_client.read(data + totalReceived, toRead);
            
            if (received > 0) 
            {
                totalReceived += received;
            }
        }

        if (millis() - startTimeout > timeoutMs)
        {
            Serial.println("Debug: receive() timed out waiting for data.");
            return; 
        }

        delay(1);
    }

    *temperature  = Connection::networkToFloat(buffer[0]);
    *humidity     = Connection::networkToFloat(buffer[1]);
    *soilMoisture = Connection::networkToFloat(buffer[2]);
    *light        = Connection::networkToFloat(buffer[3]);
}
bool Connection::isAlive(void)
{
	return WiFi.status() == WL_CONNECTED && this->m_client.connected();
}

float Connection::networkToFloat(uint32_t value)
{
	value = ntohl(value);
	float temp;
    memcpy(&temp, &value, sizeof(value));
    return temp;
}
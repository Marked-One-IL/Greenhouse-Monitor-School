#include "../include/Sensors.hpp"

#define DHTPIN 32
#define SOIL_PIN 35
#define LIGHT_PIN 34

Sensors::Sensors(void) :
	m_dht(DHTPIN, DHT11)
{
}
void Sensors::begin(void)
{
    this->m_dht.begin();
}
float Sensors::getSoilMoisture(void)
{
	int raw = analogRead(SOIL_PIN);
	
	float percent = (float)(raw - 3200) * 100.0f / (1100 - 3200);
	
	if (percent < 0.0f) percent = 0.0f;
	if (percent > 100.0f) percent = 100.0f;
	
	return percent;
}
float Sensors::getLight(void)
{
	int raw = analogRead(LIGHT_PIN);
	
	float percent = (float)raw * 100.0f / 4095.0f;
	
	if (percent < 0.0f) percent = 0.0f;
	if (percent > 100.0f) percent = 100.0f;
	
	return percent;
}
float Sensors::getTemperature(void)
{
    return this->m_dht.readTemperature();
}
float Sensors::getHumidity(void)
{
    return this->m_dht.readHumidity();
}
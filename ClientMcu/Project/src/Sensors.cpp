#include "../include/Sensors.hpp"

namespace Sensors
{
	bool isTemperatureBad(float temperature)
	{
		return (temperature < 10.0f || temperature > 35.0f);
	}

	bool isHumidityBad(float humidity)
	{
		return (humidity < 40.0f || humidity > 90.0f);
	}

	bool isSoilMoistureBad(float soilMoisture)
	{
		return (soilMoisture < 30.0f || soilMoisture > 90.0f);
	}

	bool isLightBad(float light)
	{
		return (light < 20.0f);
	}
}
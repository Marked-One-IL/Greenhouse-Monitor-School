#ifndef SENSORS_HPP
#define SENSORS_HPP

namespace Sensors
{
	bool isTemperatureBad(float temperature);
	bool isHumidityBad(float humidity);
	bool isSoilMoistureBad(float soilMoisture);
	bool isLightBad(float light);
}

#endif // SENSORS_HPP
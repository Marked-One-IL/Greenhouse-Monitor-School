#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <DHT.h>

class Sensors
{
public:
    Sensors(void);
    void begin(void);
    float getSoilMoisture(void);
    float getLight(void);
    float getTemperature(void);
    float getHumidity(void);

private:
    DHT m_dht;
};

#endif // SENSORS_HPP
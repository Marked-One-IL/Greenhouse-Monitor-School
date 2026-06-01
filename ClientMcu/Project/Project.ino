#include "include/Connection.hpp"
#include "include/Sensors.hpp"
#include "include/Screen.hpp"
#include "include/Alarm.hpp"

#define SERIAL_TRANSMISSION_SPEED 115200

#define WIFI_NAME "ENTER_WIFI_NAME"
#define WIFI_PASSWORD "ENTER_WIFI_PASSWORD"

#define SERVER_IP "ENTER_IP_OR_URL"
#define SERVER_PORT 4600

Connection connection;
Screen screen;
float temperature = 0.0f;
float humidity = 0.0f;
float soilMoisture = 0.0f;
float light = 0.0f;

void setup()
{
  Serial.begin(SERIAL_TRANSMISSION_SPEED);
  screen.begin();
  connection.begin(WIFI_NAME, WIFI_PASSWORD, SERVER_IP, SERVER_PORT);
}

void loop()
{
  Alarm::deactivate();

  if (connection.isAlive())
  {
    Serial.println("Getting sensors data");
    connection.receive(&temperature, &humidity, &soilMoisture, &light);
  }
  else
  {
    Serial.println("Connection lost! Attempting to reconnect...");
    connection.begin(WIFI_NAME, WIFI_PASSWORD, SERVER_IP, SERVER_PORT);
  }

  if (Sensors::isTemperatureBad(temperature)   || Sensors::isHumidityBad(humidity) ||
      Sensors::isSoilMoistureBad(soilMoisture) || Sensors::isLightBad(light))
  {
    Alarm::activate();
  }

  screen.draw(temperature, humidity, soilMoisture, light);
  delay(3000);
}
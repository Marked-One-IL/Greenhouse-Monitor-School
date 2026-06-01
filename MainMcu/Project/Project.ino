#include "include/Screen.hpp"
#include "include/Connection.hpp"
#include "include/Sensors.hpp"

#define SERIAL_TRANSMISSION_SPEED 115200

#define WIFI_NAME "ENTER_WIFI_NAME"
#define WIFI_PASSWORD "ENTER_WIFI_PASSWORD"

#define SERVER_IP "ENTER_IP_OR_URL"
#define SERVER_PORT 4600

Connection connection;
Screen screen;
Sensors sensors;

void setup()
{
  Serial.begin(SERIAL_TRANSMISSION_SPEED);
  connection.begin(WIFI_NAME, WIFI_PASSWORD, SERVER_IP, SERVER_PORT);
  screen.begin();
  sensors.begin();
}

void loop()
{
  float temperature = sensors.getTemperature();
  float humidity = sensors.getHumidity();
  float soilMoisture = sensors.getSoilMoisture();
  float light = sensors.getLight();

  if (connection.isAlive())
  {
    Serial.println("Sending sensors data");
    connection.send(temperature, humidity, soilMoisture, light);
  }
  else
  {
    Serial.println("Connection lost! Attempting to reconnect...");
    connection.begin(WIFI_NAME, WIFI_PASSWORD, SERVER_IP, SERVER_PORT);
  }

  screen.draw(temperature, humidity, soilMoisture, light);
  delay(3000);
}
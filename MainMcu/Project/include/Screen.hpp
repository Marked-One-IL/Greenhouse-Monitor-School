#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class Screen
{
public:
	Screen(void);
	void begin(void);
	void draw(float temperature, float humidity, float soilMoisture, float light);
	
private:
	Adafruit_ILI9341 m_tft;
};

#endif // SCREEN_HPP
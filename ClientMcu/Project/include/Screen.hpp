#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Screen
{
public:
	Screen(void);
	void begin(void);
	void draw(float temperature, float humidity, float soilMoisture, float light);
	
private:
	LiquidCrystal_I2C m_lcd;
};

#endif // SCREEN_HPP
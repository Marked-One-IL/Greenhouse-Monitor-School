#include "../include/Screen.hpp"

#define TFT_CS 21
#define TFT_RST 22
#define TFT_DC 19
#define TFT_MOSI 23
#define TFT_CLK 18
#define TFT_MISO -1

Screen::Screen(void) :
	m_tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO)
{
}

void Screen::begin(void)
{
	this->m_tft.begin();
    this->m_tft.setRotation(1);
    this->m_tft.fillScreen(ILI9341_WHITE);
	
	this->m_tft.setTextColor(ILI9341_BLACK);
    this->m_tft.setTextSize(2);
	
	// Temperature
    this->m_tft.setCursor(10, 20);
    this->m_tft.print("Temperature:");
	
	// Humidity
    this->m_tft.setCursor(10, 60);
    this->m_tft.print("Humidity:");
	
	// Soil Moisture
    this->m_tft.setCursor(10, 100);
    this->m_tft.print("Soil Moisture:");
	
	// Light
    this->m_tft.setCursor(10, 140);
    this->m_tft.print("Light:");
}

void Screen::draw(float temperature, float humidity, float soilMoisture, float light)
{
	this->m_tft.setTextSize(2);
    this->m_tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);

    char buf[32];

    // Temperature
    this->m_tft.setCursor(180, 20);
    snprintf(buf, sizeof(buf), "%.1f C  ", temperature);
    this->m_tft.print(buf);

    // Humidity
    this->m_tft.setCursor(180, 60);
    snprintf(buf, sizeof(buf), "%.1f %%  ", humidity);
    this->m_tft.print(buf);

    // Soil Moisture
    this->m_tft.setCursor(180, 100);
    snprintf(buf, sizeof(buf), "%.1f %%  ", soilMoisture);
    this->m_tft.print(buf);

    // Light
    this->m_tft.setCursor(180, 140);
    snprintf(buf, sizeof(buf), "%.1f %%  ", light);
    this->m_tft.print(buf);
}
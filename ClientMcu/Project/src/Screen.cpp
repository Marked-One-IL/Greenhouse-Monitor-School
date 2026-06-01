#include "../include/Screen.hpp"

#define LCD_SDA 21
#define LCD_SCL 22

Screen::Screen(void) :
    m_lcd(0x27, 16, 2)
{
}

void Screen::begin(void)
{
    Wire.begin(LCD_SDA, LCD_SCL);

    this->m_lcd.init();
    this->m_lcd.backlight();

    this->m_lcd.clear();

    this->m_lcd.setCursor(0, 0);
    this->m_lcd.print("System Ready");

    this->m_lcd.setCursor(0, 1);
    this->m_lcd.print("Initializing");
}
void Screen::draw(float temperature, float humidity, float soilMoisture, float light)
{
    char buf[17];

    snprintf(buf,sizeof(buf),"T:%.1f H:%.1f",temperature,humidity);

    this->m_lcd.setCursor(0, 0);
    this->m_lcd.print("                ");
    this->m_lcd.setCursor(0, 0);
    this->m_lcd.print(buf);

    snprintf(buf,sizeof(buf),"S:%.0f L:%.0f",soilMoisture,light);

    this->m_lcd.setCursor(0, 1);
    this->m_lcd.print("                ");
    this->m_lcd.setCursor(0, 1);
    this->m_lcd.print(buf);
}
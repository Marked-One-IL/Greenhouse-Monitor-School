#include "../include/Alarm.hpp"
#include <Arduino.h>

#define BUZZER_PIN 32

namespace Alarm
{
	void activate(void)
	{
		tone(BUZZER_PIN, 2048);
	}
	void deactivate(void)
	{
		noTone(BUZZER_PIN);
	}
}

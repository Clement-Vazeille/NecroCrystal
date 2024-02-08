#include "Timer.h"

Timer::Timer() :
	miliseconds(0),seconds(0),minutes(0)
{
}

void Timer::Add(float deltaTime)
{
	miliseconds += deltaTime;

	seconds += ((int)miliseconds) / 1000;
	miliseconds -= (((int)miliseconds) / 1000)*1000;  //remove thousands

	
	minutes += seconds / 60;
	seconds = seconds % 60;

	if (minutes >= 100)
	{
		seconds = 59;
		miliseconds = 999;
		minutes = 99;
	}
}

void Timer::Reset(void)
{
	miliseconds = 0;
	seconds = 0;
	minutes = 0;
}

std::string Timer::ToString(void) const
{
	std::string minutesString = std::to_string(minutes / 10) + std::to_string(minutes % 10);
	std::string secondsString = std::to_string(seconds / 10) + std::to_string(seconds % 10);
	int milisecondsInt = (int)miliseconds;
	std::string milisecondsString = std::to_string(milisecondsInt / 100) + std::to_string((milisecondsInt % 100)/10) + std::to_string(milisecondsInt % 10);
	return minutesString + "m " + 
		secondsString + "s " + milisecondsString + "ms";
}

std::string Timer::ToMiniString(void) const
{
	std::string minutesString = std::to_string(minutes / 10) + std::to_string(minutes % 10);
	std::string secondsString = std::to_string(seconds / 10) + std::to_string(seconds % 10);
	int milisecondsInt = (int)miliseconds;
	std::string milisecondsString = std::to_string(milisecondsInt / 100);
	return minutesString + "m " +
		secondsString + "." + milisecondsString + "s";
}

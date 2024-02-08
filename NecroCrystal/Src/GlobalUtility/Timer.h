#pragma once
#include <string>
class Timer
{
protected:
	float miliseconds; //entre 0 et 999, display que les entiers
	int seconds; //entre 0 et 59
	int minutes; //entre 0 et 99
public:
	Timer();

	void Add(float deltaTime);
	void Reset(void);
	std::string ToString(void) const;
	std::string ToMiniString(void) const;

};


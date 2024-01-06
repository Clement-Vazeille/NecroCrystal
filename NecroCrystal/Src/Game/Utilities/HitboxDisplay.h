#pragma once
class HitboxDisplay
{
protected:
	bool value;
	float timer;
	float refreshRate;
public:
	HitboxDisplay();

	void Update(float deltaTime);
	bool getValue(void) const;
};
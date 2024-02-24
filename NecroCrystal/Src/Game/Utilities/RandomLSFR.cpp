#include "RandomLSFR.h"

int RandomLSFR::iterateLSFR(void)
{
    int ans = registre%2;
	registre = (registre>>1) | ((unsigned long long) (this->countBit(registre & key)%2) << 50);
	return ans;
}

int RandomLSFR::countBit(unsigned long long u) const
{
	unsigned long long ans = u;
	while (u > 0)
	{
		u = u >> 1;
		ans -= u;
	}
    return ans;
}

int RandomLSFR::countBitSize(int n) const
{
	int ans = 0;
	while (n > 0)
	{
		n = n >> 1;
		++ans;
	}
	return ans;
}

RandomLSFR::RandomLSFR()
{
	registre = 1024568945123548;
	key = 1101564684769200;
}

int RandomLSFR::randomUpTo(int n)
{
	int ans = n + 1;
	int bitNumber = this->countBitSize(n);
	while (ans > n)
	{
		ans = 0;
		for (int i = 0; i < bitNumber; i++)
		{
			ans = (ans << 1) | iterateLSFR();
		}
	}
	return ans;
}

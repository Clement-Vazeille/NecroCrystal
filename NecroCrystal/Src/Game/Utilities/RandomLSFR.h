#pragma once
class RandomLSFR //50 bit lsfr to generate random number
{
protected:
	unsigned long long registre; // <= 2^50
	unsigned long long key;      //same length than above
	
	int iterateLSFR(void); //iterate the LSFR and return the generated bit
	int countBit(unsigned long long u) const;
	int countBitSize(int n) const;
public:
	RandomLSFR();
	int randomUpTo(int n);//give a random number between 0 and n
};


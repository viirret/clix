#ifndef GUN_HH
#define GUN_HH

#include <string>

class Gun
{
	public:
		Gun(std::string name);
		~Gun();
		int magSize;
		int rateOfFire;
		int currentCapacity;
};

#endif


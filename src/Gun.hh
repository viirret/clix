#ifndef GUN_HH
#define GUN_HH

#include <string>

class Gun
{
	public:
		Gun(std::string name);
		~Gun();
		void fire();
		std::string capacity;
		std::string magazineSize;
		std::string rateOfFire;
	private:
		void updateAmmo();
		int intMagazineSize;
		int intRateOfFire;
		int intCapacity;
};

#endif


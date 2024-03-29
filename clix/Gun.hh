#ifndef GUN_HH
#define GUN_HH

#include <string>

class Gun
{
	public:
		Gun(std::string name);
		~Gun();
		void fire();
		void restock();
		std::string capacity;
		std::string magazineSize;
		std::string rateOfFire;
		int getCapacity();
		int getMagazineSize();
		int getRateOfFire();
	private:
		void updateAmmo();
		int intMagazineSize;
		int intRateOfFire;
		int intCapacity;
};

#endif


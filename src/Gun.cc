#include "Gun.hh"

Gun::Gun(std::string name)
{
	if(name == "example")	
	{
		intMagazineSize = 30;
		intRateOfFire = 100;
		intCapacity = 30;
	}

	capacity = std::to_string(intCapacity);
	magazineSize = std::to_string(intMagazineSize);
	rateOfFire = std::to_string(intMagazineSize);
}

Gun::~Gun()
{
}

void Gun::fire()
{
	if(intCapacity > 0)
	{
		intCapacity--;
		capacity = std::to_string(intCapacity);
	}
}

int Gun::getCapacity() { return intCapacity; }
int Gun::getRateOfFire() { return intRateOfFire; }
int Gun::getMagazineSize() { return intMagazineSize; }


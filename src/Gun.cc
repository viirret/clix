#include "Gun.hh"

Gun::Gun(std::string name)
{
	if(name == "example")	
	{
		magSize = 30;
		rateOfFire = 100;
		currentCapacity = 30;
	}
}

Gun::~Gun()
{

}

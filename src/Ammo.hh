#ifndef AMMO_HH
#define AMMO_HH

#include "Object.hh"

class Ammo : public Object
{
	public:
		Ammo(const char* path, int width, int height);
};

#endif
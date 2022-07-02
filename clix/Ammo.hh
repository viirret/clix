#ifndef AMMO_HH
#define AMMO_HH

#include "Object.hh"

class Ammo : public Object
{
	public:
		Ammo(const char* path, Vec2f position);
};

#endif

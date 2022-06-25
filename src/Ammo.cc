#include "Ammo.hh"

Ammo::Ammo(const char* path, int width, int height) : Object(path, width, height)
{
	type = Object::Type::ammo;
}



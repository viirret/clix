#include "Ammo.hh"

Ammo::Ammo(const char* path, Vec2f position) : Object(path, position)
{
	type = Object::Type::ammo;
}



#ifndef ENEMY_HH
#define ENEMY_HH

#include "Object.hh"

class Enemy : public Object
{
	public:
		Enemy(const char* path, int width, int height);
};

#endif

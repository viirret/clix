#include "Enemy.hh"

Enemy::Enemy(const char* path, int width, int height) : Object(path, width, height)
{
	type = Object::Type::enemy;
}


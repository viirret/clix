#include "Enemy.hh"

Enemy::Enemy(const char* path, Vec2f position) : Object(path, position)
{
	type = Object::Type::enemy;
}


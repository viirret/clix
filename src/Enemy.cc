#include "Enemy.hh"

Enemy::Enemy(const char* path, Vec2f position) : Object(path, position)
{
	type = Object::Type::enemy;
}

Enemy::Enemy(const char* path) : Object(path)
{
	type = Object::Type::enemy;
}


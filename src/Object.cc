#include "Object.hh"

Object::Object(const char* path, int width, int height) : 	
								x(width),
								y(height)
{
	texture = LoadTexture(path);
}

Object::~Object()
{
	UnloadTexture(texture);
}

void Object::setTexture(const char* path)
{
	texture = LoadTexture(path);
}

bool Object::checkHit(Vector2 hit)
{
	return hit.x >= x && hit.x <= x + texture.width && hit.y >= y && hit.y <= y + texture.height;
}


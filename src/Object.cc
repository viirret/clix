#include "Object.hh"

Object::Object(const char* path, int width, int height) : 	
					posX(width),
					posY(height)
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
	return hit.x >= posX && hit.x <= posX + texture.width && hit.y >= posY && hit.y <= posY + texture.height;
}


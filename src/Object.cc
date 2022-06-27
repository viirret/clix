#include "Object.hh"

Object::Object(const char* path, int width, int height) : 	
								type(Object::Type::object),
								x(width),
								y(height)
{
	setTexture(path);
}

Object::Object(const char* path) :
			type(Object::Type::object)
{
	setTexture(path);
}

Object::~Object()
{
	UnloadTexture(texture);
}

void Object::setTexture(const char* path) { texture = LoadTexture(path); }
void Object::setX(int x) { this->x = x; }
void Object::setY(int y) { this->y = y; }

void Object::draw(Color color)
{
	DrawTexture(texture, x, y, color);
}

bool Object::checkHit(Vec2f hit)
{
	return hit.x >= x && hit.x <= x + texture.width && hit.y >= y && hit.y <= y + texture.height;
}


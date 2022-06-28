#include "Object.hh"

Object::Object(const char* path, float width, float height) : 	
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

void Object::moveTowardsTarget()
{
	if(x < target.x)
		x += speed.x;

	if(x > target.x)
		x -= speed.x; 

	if(y < target.y)
		y += speed.y;

	if(y > target.y)
		y -= speed.y;
}

void Object::draw(Color color)
{
	DrawTexture(texture, x, y, color);
}

bool Object::checkHit(Vec2f hit)
{
	return hit.x >= x && hit.x <= x + texture.width && hit.y >= y && hit.y <= y + texture.height;
}

// setters
void Object::setTexture(const char* path) { texture = LoadTexture(path); }
void Object::setTarget(Vec2f target) { this->target = target; }
void Object::setTargetX(float x) { target.x = x; }
void Object::setTargetY(float y) { target.y = y; }
void Object::setSpeed(Vec2f speed) { this->speed = speed; }
void Object::setSpeedX(float x) { speed.x = x; }
void Object::setSpeedY(float y) { speed.y = y; }
void Object::setX(float x) { this->x = x; }
void Object::setY(float y) { this->y = y; }

// getters
Texture Object::getTexture() { return texture; }
Vec2f Object::getTarget() { return target; }
Vec2f Object::getSpeed() { return speed; }
float Object::getX() { return x; }
float Object::getY() { return y; }


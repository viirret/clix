#include "Object.hh"

Object::Object(const char* path, Vec2f position, Vec2f speed, Vec2f target)
						: 	type(Object::Type::object),
							position(position),
							speed(speed),
							target(target)
{
	setTexture(path);
}

Object::Object(const char* path, Vec2f position, Vec2f speed)
						:	type(Object::Type::object),
							position(position),
							speed(speed)
{
	setTexture(path);
}

Object::Object(const char* path, Vec2f position) 
						: 	type(Object::Type::object),
							position(position)
{
	setTexture(path);
}

Object::Object(const char* path)
						: type(Object::Type::object)
{
	setTexture(path);
}

Object::~Object()
{
	UnloadTexture(texture);
}

Vec2f Object::randomPositionOnScreen()
{
	float x = rnd<float>::randomValue(0.f, GetScreenWidth() - getWidth());
	float y = rnd<float>::randomValue(0.f, GetScreenHeight() - getHeight());
	return Vec2f(x, y);
}

void Object::moveTowardsTarget()
{
	if(position.x < target.x)
		position.x += speed.x;

	if(position.x > target.x)
		position.x -= speed.x; 

	if(position.y < target.y)
		position.y += speed.y;

	if(position.y > target.y)
		position.y -= speed.y;
}

void Object::draw(Color color)
{
	DrawTexture(texture, position.x, position.y, color);
}

bool Object::checkHit(Vec2f hit)
{
	return hit.x >= position.x && hit.x <= position.x + texture.width && hit.y >= position.y && hit.y <= position.y + texture.height;
}

// setters
void Object::setType(Object::Type type) { this->type = type; }
void Object::setTexture(const char* path) { texture = LoadTexture(path); }
void Object::setTarget(Vec2f target) { this->target = target; }
void Object::setTargetX(float x) { target.x = x; }
void Object::setTargetY(float y) { target.y = y; }
void Object::setSpeed(Vec2f speed) { this->speed = speed; }
void Object::setSpeedX(float x) { speed.x = x; }
void Object::setSpeedY(float y) { speed.y = y; }
void Object::setPosition(Vec2f position) { this->position = position; };
void Object::setX(float x) { position.x = x; }
void Object::setY(float y) { position.y = y; }

void Object::setRandomTarget()
{
	setTarget(randomPositionOnScreen());	
}

void Object::setRandomSpeed()
{
	setSpeed(randomPositionOnScreen());
}

void Object::setRandomPosition()
{
	setPosition(randomPositionOnScreen());
}

// getters
Texture Object::getTexture() { return texture; }
Vec2f Object::getTarget() { return target; }
Vec2f Object::getSpeed() { return speed; }
float Object::getX() { return position.x; }
float Object::getY() { return position.y; }
float Object::getWidth() { return texture.width; }
float Object::getHeight() { return texture.height; }


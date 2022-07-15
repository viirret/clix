#include "Object.hh"

Object::Object(Vec2f position) 
						: position(position)
{
	id = "No ID!";
}

Object::Object(std::string id)
						: id(id)
{
}

Object::Object(Vec2f position, std::string id)
						: id(id), position(position)
{
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

void Object::draw(Color color)
{
	DrawTexture(texture, position.x, position.y, color);
}

void Object::draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}

bool Object::checkHit(Vec2f hit)
{
	return hit.x >= position.x && hit.x <= position.x + texture.width && hit.y >= position.y && hit.y <= position.y + texture.height;
}

// setters
void Object::setId(std::string id) { this->id = id; }
void Object::setTexture(const char* path) { texture = LoadTexture(path); }
void Object::setPosition(Vec2f position) { this->position = position; };
void Object::setX(float x) { position.x = x; }
void Object::setY(float y) { position.y = y; }

void Object::setRandomPosition()
{
	setPosition(randomPositionOnScreen());
}

// getters
Texture Object::getTexture() { return texture; }
float Object::getX() { return position.x; }
float Object::getY() { return position.y; }
float Object::getWidth() { return texture.width; }
float Object::getHeight() { return texture.height; }


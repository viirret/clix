#include "Entity.hh"

Entity::Entity(std::string path, Vec2f position, Vec2f speed, Vec2f target)
	: Img(path, position), speed(speed), target(target)
{
}

Entity::Entity(std::string path, Vec2f position, Vec2f target)
	: Img(path, position), target(target)
{
}

void Entity::moveTowardsTarget()
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



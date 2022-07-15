#ifndef ENTITY_HH
#define ENTITY_HH

#include "Image.hh"

class Entity : public Img
{
	public:
		Entity(std::string path, Vec2f position, Vec2f speed, Vec2f target);
		Entity(std::string path, Vec2f position, Vec2f target);
		void moveTowardsTarget();

		Vec2f speed, target;
};

#endif

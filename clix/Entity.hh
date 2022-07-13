#ifndef ENTITY_HH
#define ENTITY_HH

#include "Image.hh"

class Entity : public Img
{
	public:
		Entity(std::string id, Vec2f position, Vec2f speed, Vec2f target);
	private:
		Vec2f position, speed, target;
};

#endif

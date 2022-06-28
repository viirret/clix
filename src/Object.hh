#ifndef OBJECT_HH
#define OBJECT_HH

#include "raylib.h"
#include "Vector2.hh"
#include <cstdio>

class Object
{
	public:
		enum class Type
		{
			object,
			ammo,
			enemy
		};
		Type type;

		Object() {};
		Object(const char* path, float width, float height);
		Object(const char* path);
		~Object();
		
		// check if texture is clicked with mouse
		bool checkHit(Vec2f hit);

		// possibility to reset texture
		void setTexture(const char* path);

		void setTarget(Vec2f target);
		void setSpeed(Vec2f speed);

		bool changePosition(Vec2f pos);

		void setX(float x);
		void setY(float y);

		void draw(Color color);

		void move();

		int getX();
		int getY();

	protected:
		// raylib texture attached to the object
		Texture texture;

		// position coordinates
		float x;
		float y;

		Vec2f speed = Vec2f(0.01f, 0.01f);

		Vec2f target;
};

#endif

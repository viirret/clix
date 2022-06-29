#ifndef OBJECT_HH
#define OBJECT_HH

#include "raylib.h"
#include "Vector2.hh"
#include "Global.hh"
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
		Object(const char* path, Vec2f position, Vec2f speed, Vec2f target);
		Object(const char* path, Vec2f position, Vec2f speed);
		Object(const char* path, Vec2f position);
		Object(const char* path);

		~Object();
		
		// check if texture is clicked with mouse
		bool checkHit(Vec2f hit);

		// final rendering function
		void draw(Color color);

		void moveTowardsTarget();

		// setters
		void setType(Object::Type type);
		void setTexture(const char* path);
		void setTarget(Vec2f target);
		void setTargetX(float x);
		void setTargetY(float y);
		void setSpeed(Vec2f speed);
		void setSpeedX(float x);
		void setSpeedY(float y);
		void setPosition(Vec2f position);
		void setX(float x);
		void setY(float y);

		// randomized setters
		void setRandomTarget();
		void setRandomPosition();
		void setRandomSpeed();

		// getters
		Texture getTexture();
		Vec2f getTarget();
		Vec2f getSpeed();
		float getX();
		float getY();
		float getWidth();
		float getHeight();

	protected:
		// raylib texture attached to the object
		Texture texture;

		// position coordinates
		Vec2f position;

		// movement speed
		Vec2f speed = Vec2f(0.01f, 0.01f);

		Vec2f target;
	private:
		Vec2f randomPositionOnScreen();

};

#endif

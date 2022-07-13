#ifndef OBJECT_HH
#define OBJECT_HH

#include "raylib.h"
#include "Vector2.hh"
#include "Global.hh"
#include <cstdio>

class Object
{
	public:
		// identifier for custom groups
		std::string id;

		// some constructors to be called from derived classed
		// TODO flip position and id arguments
		Object() {};
		Object(std::string id);
		Object(Vec2f position);
		Object(Vec2f position, std::string id);
		~Object();
		
		// check if texture is clicked with mouse
		bool checkHit(Vec2f hit);

		// final rendering function
		virtual void draw(Color color);
		virtual void draw();

		// setters
		void setId(std::string id);
		void setTexture(const char* path);
		void setPosition(Vec2f position);
		void setX(float x);
		void setY(float y);

		// randomized setters
		//void setRandomTarget();
		void setRandomPosition();
		//void setRandomSpeed();

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

	private:
		Vec2f randomPositionOnScreen();

};

#endif

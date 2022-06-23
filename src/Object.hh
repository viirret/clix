#ifndef OBJECT_HH
#define OBJECT_HH

#include "raylib.h"
#include "Vector2.hh"

class Object
{
	public:
		Object(const char* path, int width, int height);
		Object(const char* path);
		~Object();

		// possibility to reset texture
		void setTexture(const char* path);

		// check if texture is clicked with mouse
		bool checkHit(Vec2f hit);

		// raylib texture attached to the object
		Texture texture;

		// position coordinates
		int x;
		int y;
	private:
		int speed;
};

#endif

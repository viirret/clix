#ifndef OBJECT_HH
#define OBJECT_HH

#include "raylib.h"
#include "Vector2.hh"

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

		Object(const char* path, int width, int height);
		Object(const char* path);
		~Object();
		
		// check if texture is clicked with mouse
		bool checkHit(Vec2f hit);

		// possibility to reset texture
		void setTexture(const char* path);

		void draw(Color color);

	protected:
		// raylib texture attached to the object
		Texture texture;

		// position coordinates
		int x;
		int y;

		int speed;
};

#endif

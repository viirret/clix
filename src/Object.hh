#ifndef OBJECT_HH
#define OBJECT_HH

#include "raylib.h"

class Object
{
	public:
		Object(const char* path, int width, int height);
		~Object();
		void setTexture(const char* path);
		bool checkHit(Vector2 hit);
		
		Texture texture;
		int speed;
		int posX;
		int posY;
};

#endif

#ifndef PLAYER_HH
#define PLAYER_HH

#include "raylib.h"

class Player
{
	public:
		Player(const char* path, int width, int height);
		~Player();
		void setTexture(const char* path);
		
		Texture texture;
		int speed;
		int posWidth;
		int posHeight;
};

#endif

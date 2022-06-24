#ifndef CROSSHAIR_HH
#define CROSSHAIR_HH

#include "raylib.h"
#include "Vector2.hh"

class Crosshair
{
	public:
		Crosshair();
		~Crosshair();
		void updateCrosshair(Vec2f pos);
		Texture texture;
		int x;
		int y;
};
#endif

#ifndef CROSSHAIR_HH
#define CROSSHAIR_HH

#include "raylib.h"

class Crosshair
{
	public:
		Crosshair();
		~Crosshair();
		void updateCrosshair(Vector2 pos);
		Texture texture;
		int x;
		int y;
};
#endif

#ifndef CROSSHAIR_HH
#define CROSSHAIR_HH

#include "raylib.h"
#include <string>
#include "Config.hh"
#include "Vector2.hh"

class Crosshair
{
	public:
		Crosshair();
		Crosshair(std::string path);
		~Crosshair();
		void updateCrosshair(Vec2f pos);
		void draw(Color color);
		void draw();
	private:
		Texture texture;
		int x;
		int y;
};
#endif

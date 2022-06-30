#ifndef GAME_HH
#define GAME_HH

#include "Core.hh"
#include "Crosshair.hh"

class Game : public Core
{
	public:
		Game();
		void update();
	private:
		void draw();
		void gameLogic();
		void updateCrosshair();
		Crosshair crosshair;
};

#endif

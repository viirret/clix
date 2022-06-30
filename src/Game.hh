#ifndef GAME_HH
#define GAME_HH

#include "Core.hh"
#include "Player.hh"
#include "Crosshair.hh"

class Game : public Core
{
	public:
		Game();
		void update();
	private:
		void draw();
		void updateGame();
		void resetGame();
		void gameOver();

		// instances of other classes
		Crosshair crosshair;
		Player player;
		Object resetButton;

		// variables for gameplay
		int killedEnemies;
		std::string killedString;
		bool isGameOver = false;
		bool currentHitChanged = false;
};

#endif

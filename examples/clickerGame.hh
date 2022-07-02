#ifndef CLICKERGAME_HH
#define CLICKERGAME_HH

#include "../src/Core.hh"
#include "../src/Player.hh"
#include "../src/Crosshair.hh"

class clickerGame : public Core
{
	public:
		clickerGame();
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

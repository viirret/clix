#ifndef CLICKERGAME_HH
#define CLICKERGAME_HH

#include "../clix/Core.hh"
#include "../clix/Player.hh"
#include "../clix/Crosshair.hh"

class clickerGame : public Core
{
	public:
		clickerGame();
		void update() override; 
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

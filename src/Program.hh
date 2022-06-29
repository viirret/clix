#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "raylib.h"
#include <memory>
#include <random>
#include "Controls.hh"
#include "Settings.hh"
#include "Object.hh"
#include "Global.hh"
#include "Initializer.hh"
#include "Crosshair.hh"
#include "Player.hh"
#include "Audio.hh"
#include "Vector2.hh"
#include "Ammo.hh"
#include "Enemy.hh"

class Program
{
	public:
		Program();
		~Program();
		void run();
		bool close;
	private:
		void draw();
		void events();
		void updateGame();
		void resetGame();
		void gameOver();
		void objectMovement();

		// add new enemy to random location on screen
		void spawnEnemyRandom(std::string texture);

		// items currently existing on screen
		std::vector<std::unique_ptr<Object>> objects;

		// instances of other classes in Program
		Initializer initializer;
		Crosshair crosshair;
		Player player;
		Audio audio;
		Object resetButton;

		// mouse tracking
		Vec2f currenthit;
		Vec2f mousePosition;

		// trackers
		int killedEnemies;
		std::string killedString;
		bool gameIsOver = false;
		bool currentHitChanged = false;

};

#endif

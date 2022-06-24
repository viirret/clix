#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "raylib.h"
#include <memory>
#include <cstdio>
#include <vector>
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
		void setVariables();
		void setSpawns();
		void spawnEnemyRandom(std::string texture);
		void spawnEnemy(std::string texture, int index);
		std::vector<std::unique_ptr<Object>> objects;
		std::vector<Vec2f> spawns;
		Vec2f currenthit;
		Vec2f mousePosition;
		Initializer initializer;
		Crosshair crosshair;
		Player player;
		Audio audio;
		int killedEnemies;
		std::string killedString;
};

#endif

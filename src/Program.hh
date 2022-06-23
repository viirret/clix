#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "raylib.h"
#include <memory>
#include <cstdio>
#include <vector>
#include "Controls.hh"
#include "Settings.hh"
#include "Object.hh"
#include "Initializer.hh"
#include "Crosshair.hh"
#include "Player.hh"

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
		std::vector<std::unique_ptr<Object>> objects;
		Vector2 currenthit;
		Vector2 mousePosition;
		Initializer initializer;
		Crosshair crosshair;
		Player player;
		int killedEnemies;
		std::string killedString;
};

#endif

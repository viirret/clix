#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "raylib.h"
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
		Initializer initializer;
		std::vector<Object*> objects;
		Vector2 currenthit;
		Vector2 mousePosition;
		Crosshair crosshair;
		Player player;
};

#endif

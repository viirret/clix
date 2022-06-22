#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "raylib.h"
#include <cstdio>
#include "Controls.hh"
#include "Settings.hh"
#include "Player.hh"
#include "Initializer.hh"

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
		void movement();
		Initializer initializer;
		Player player;
};

#endif

#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "raylib.h"
#include <cstdio>
#include "Controls.hh"
#include "Settings.hh"
#include "Object.hh"
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
		bool checkHit(Object o);
		Initializer initializer;
		Object arch;
		Vector2 currenthit;
		int hitX;
		int hitY;
};

#endif

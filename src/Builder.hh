#ifndef BUILDER_HH
#define BUILDER_HH

#include "Program.hh"
#include "Game.hh"

class Builder
{
	public:
		Builder();
		bool close = false;
		void update();
		Program program;
		Game game;
};

#endif

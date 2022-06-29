#ifndef BUILDER_HH
#define BUILDER_HH

#include "Program.hh"
#include "PlayGround.hh"

class Builder
{
	public:
		Builder();
		bool close = false;
		void update();
		Program program;
		PlayGround playGround;
};

#endif

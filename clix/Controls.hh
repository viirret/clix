#ifndef CONTROLS_HH
#define CONTROLS_HH

#include "raylib.h"

namespace Controls
{
	bool left();
	bool right();
	bool up();
	bool down();
	bool leftOnly();
	bool rightOnly();
	bool upOnly();
	bool downOnly();
	bool space();
	bool spaceOnce();
};

#endif

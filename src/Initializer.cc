#include "Initializer.hh"

Initializer::Initializer()
{
	// init raylib window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "");
}

Initializer::~Initializer()
{
	CloseWindow();
}

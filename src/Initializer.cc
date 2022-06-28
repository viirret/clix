#include "Initializer.hh"

Initializer::Initializer()
{
	// init raylib window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "");
	HideCursor();
}

Initializer::~Initializer()
{
	CloseWindow();
}

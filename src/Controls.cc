#include "Controls.hh"

bool Controls::left()
{
	return IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_H);
}

bool Controls::right()
{
	return IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_L);
}

bool Controls::jump()
{
	return IsKeyDown(KEY_SPACE);
}


#include "Controls.hh"

bool Controls::left()
{
	return IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_H);
}

bool Controls::right()
{
	return IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_L);
}

bool Controls::up()
{
	return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_J);
}

bool Controls::down()
{
	return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_K);
}

bool Controls::leftOnly()
{
	return left() && !up() && !down() && !right();
}

bool Controls::rightOnly()
{
	return right() && !left() && !up() && !down();
}

bool Controls::upOnly()
{
	return up() && !right() && !left() && !down();
}

bool Controls::downOnly()
{
	return down() && !up() && !right() && !left();
}

bool Controls::space()
{
	return IsKeyDown(KEY_SPACE);
}

bool Controls::spaceOnce()
{
	return IsKeyPressed(KEY_SPACE);
}


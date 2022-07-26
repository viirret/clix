#include "Controls.hh"

bool Controls::left()
{
	return IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_H);
}

bool Controls::leftOnce()
{
	return IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_H);
}

bool Controls::right()
{
	return IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_L);
}

bool Controls::rightOnce()
{
	return IsKeyPressed(KEY_A) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_L);
}

bool Controls::up()
{
	return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_J);
}

bool Controls::upOnce()
{
	return IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_J);
}

bool Controls::down()
{
	return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_K);
}

bool Controls::downOnce()
{
	return IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_K);
}

bool Controls::leftOnly()
{
	return left() && !up() && !down() && !right();
}

bool Controls::leftOnlyOnce()
{
	return leftOnce() && !upOnce() && !downOnce() && !rightOnce();
}

bool Controls::rightOnly()
{
	return right() && !left() && !up() && !down();
}

bool Controls::rightOnlyOnce()
{
	return rightOnce() && !leftOnce() && !upOnce() && !downOnce();
}

bool Controls::upOnly()
{
	return up() && !right() && !left() && !down();
}

bool Controls::upOnlyOnce()
{
	return upOnce() && !rightOnce() && !leftOnce() && !downOnce();
}

bool Controls::downOnly()
{
	return down() && !up() && !right() && !left();
}

bool Controls::downOnlyOnce()
{
	return downOnce() && !upOnce() && !rightOnce() && !leftOnce();
}

bool Controls::space()
{
	return IsKeyDown(KEY_SPACE);
}

bool Controls::spaceOnce()
{
	return IsKeyPressed(KEY_SPACE);
}


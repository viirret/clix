#include "Crosshair.hh"

Crosshair::Crosshair()
{
	texture = LoadTexture("../assets/crosshair.png");
}

Crosshair::~Crosshair()
{
	UnloadTexture(texture);
}

void Crosshair::updateCrosshair(Vec2f pos)
{
	x = pos.x - (float)texture.width / 2;
	y = pos.y - (float)texture.height / 2;
}

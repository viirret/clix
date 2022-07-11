#include "Crosshair.hh"

Crosshair::Crosshair()
{
	texture = LoadTexture("../assets/crosshair.png");
}

Crosshair::Crosshair(std::string path)
{
	texture = LoadTexture((Config::ASSETSPATH + path).c_str());
}

Crosshair::~Crosshair()
{
	UnloadTexture(texture);
}

void Crosshair::draw(Color color)
{
	DrawTexture(texture, x, y, color);
}

void Crosshair::draw()
{
	DrawTexture(texture, x, y, WHITE);
}

void Crosshair::updateCrosshair(Vec2f pos)
{
	x = pos.x - (float)texture.width / 2;
	y = pos.y - (float)texture.height / 2;
}

#include "Image.hh"

Img::Img(std::string path, Vec2f position) : position(position)
{
	image = LoadImage(path.c_str());
	texture = LoadTextureFromImage(image);
}

void Img::draw(Color color)
{
	DrawTexture(texture, position.x, position.y, color);
}

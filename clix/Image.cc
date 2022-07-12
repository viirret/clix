#include "Image.hh"

Img::Img(std::string path, Vec2f position) : Object(position)
{
	image = LoadImage((Config::ASSETSPATH + path).c_str());
	updateTexture();
}

Img::Img(std::string path)
{
	image = LoadImage((Config::ASSETSPATH + path).c_str());
	position = Vec2f(0, 0);
	updateTexture();
}

void Img::draw(Color color)
{
	DrawTexture(texture, position.x, position.y, color);
}

void Img::draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}

void Img::resizeImage(Vec2f size)
{
	ImageResize(&image, size.x, size.y);
	updateTexture();
}

void Img::updateTexture()
{
	texture = LoadTextureFromImage(image);
}

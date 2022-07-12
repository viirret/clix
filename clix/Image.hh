#ifndef IMAGE_HH
#define IMAGE_HH

#include "raylib.h"
#include <string>
#include "Object.hh"
#include "Config.hh"

class Img : public Object
{
	public:
		Img(std::string path, Vec2f position);
		Img(std::string path);
		void draw(Color color) override;
		void draw() override;
		void resizeImage(Vec2f size);
	private:
		void updateTexture();
		Image image;
};

#endif

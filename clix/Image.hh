#ifndef IMAGE_HH
#define IMAGE_HH

#include "raylib.h"
#include <string>
#include "Object.hh"

class Img : public Object
{
	public:
		Img(std::string path, Vec2f position);
		void draw(Color color) override;
	private:
		// the actual image
		Image image;
		Texture texture;
		Vec2f position;
};

#endif

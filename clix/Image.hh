#ifndef IMAGE_HH
#define IMAGE_HH

#include "raylib.h"
#include <string>
#include <vector>
#include "Object.hh"
#include "Config.hh"

class Img : public Object
{
	public:
		Img(std::string path, Vec2f position, std::string id);
		Img(std::string path, Vec2f position);
		Img(std::string path, std::string id);
		Img(std::string path);
		Img() {};

		void draw(Color color) override;
		void draw() override;
		void resizeImage(Vec2f size);

		void changeTexture(std::string path);
	private:
		void updateTexture();
		Image image;
		std::vector<std::string> paths;
		std::vector<Image> images;
};

#endif

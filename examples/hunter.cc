#include "../clix/Core.hh"
#include "../clix/Object.hh"
#include "../clix/Image.hh"

class Hunter : public Core
{
	public:
		Hunter() 
			: 	Core(), 
				background(Config::ASSETSPATH + "hunter/village.png"), 
				car(Config::ASSETSPATH + "hunter/car.png", Vec2f((float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3))
		{
			resizeImages();
		}

		void update() override
		{
			Core::update();

			if(screenResized)
			{
				resizeImages();
			}
			background.draw();
			car.draw();
		}

		void resizeImages()
		{
			background.resizeImage(Vec2f(GetScreenWidth(), GetScreenHeight()));
			car.resizeImage(Vec2f((float)GetScreenWidth() / 5, (float)GetScreenHeight() / 5));
		}

	private:
		Img background, car;
};

int main(int argc, char** agrv)
{
	Hunter h;
	h.start();
	return 0;
}

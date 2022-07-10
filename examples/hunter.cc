#include "../clix/Core.hh"
#include "../clix/Object.hh"
#include "../clix/Image.hh"

class Hunter : public Core
{
	public:
		Hunter() : Core(), background(Config::ASSETSPATH + "hunter/village.png", Vec2f(0, 0))
		{
		}

		void update() override
		{
			Core::update();

			//background.resizeImage(Vec2f(GetScreenWidth(), GetScreenHeight()));

			background.draw(WHITE);
		}

	private:
		Img background;
};

int main(int argc, char** agrv)
{
	Hunter h;
	h.start();
	return 0;
}

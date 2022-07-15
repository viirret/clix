#include "../clix/Core.hh"
#include "../clix/Object.hh"
#include "../clix/Image.hh"
#include "../clix/Entity.hh"

class Enemy : public Entity
{
	public:
		Enemy(std::string path, Vec2f position, Vec2f target) : Entity(path, position, target)
		{
			// speed of Entity
			speed = Vec2f(1.0f, 1.0f);

			// id of the Object
			id = "enemy";
		}
};

class Hunter : public Core
{
	public:
		Hunter() 
			: 	Core(), 
				background(Config::ASSETSPATH + "hunter/village.png"), 
				car(Config::ASSETSPATH + "hunter/car.png", Vec2f((float)GetScreenWidth() / 0.8f, (float)GetScreenHeight() / 0.5f))
		{
			resizeImages();

			// creating enemies
			for(size_t i = 0; i < 5; i++)
			{
				switch(i)
				{
					case 0: enemies.push_back(Enemy("hunter/d1.png", Vec2f(0, 0), Vec2f(1, 0))); break;
					case 1: enemies.push_back(Enemy("hunter/d2.png", Vec2f(100, 100), Vec2f(500, 500))); break;
				}
			}
		}

		void update() override
		{
			Core::update();

			if(screenResized)
				resizeImages();


			background.draw();
			car.draw();

			for(auto& enemy : enemies)
			{
				enemy.draw();
			}

		}

		void resizeImages()
		{
			background.resizeImage(Vec2f(GetScreenWidth(), GetScreenHeight()));
			car.resizeImage(Vec2f((float)GetScreenWidth() / 5, (float)GetScreenHeight() / 5));
		}

	private:
		Img background, car;
		std::vector<Enemy> enemies;

};

int main(int argc, char** agrv)
{
	Hunter h;
	h.start();
	return 0;
}

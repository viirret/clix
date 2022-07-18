#include "../clix/Core.hh"
#include "../clix/Object.hh"
#include "../clix/Image.hh"
#include "../clix/Entity.hh"

class Enemy : public Entity
{
	public:
		Enemy(std::string path, Vec2f position, Vec2f target, std::string sound) : Entity(path, position, target), sound(sound)
		{
			// speed of Entity
			speed = Vec2f(0.f, 0.1f);

			// id of the Object
			id = "enemy";
		}

		std::string sound;

		void resize()
		{
			resizeImage(Vec2f((float)GetScreenWidth() / 20, (float)GetScreenWidth() / 20));
		}

};

class Hunter : public Core
{
	public:
		Hunter() 
			: 	Core(), 
				background("hunter/village.png"), 
				car("hunter/car.png", Vec2f((float)GetScreenWidth() / 0.8f, (float)GetScreenHeight() / 0.5f))
		{
			createSpawns();

			for(int i = 0; i < 5; i++)
			{
				spawnEnemy(i);
			}

			resizeImages();
		}


		void createSpawns()
		{
			coords.emplace_back(Vec2f((float)GetScreenWidth() / 10, GetScreenHeight() / 0.9), Vec2f(0.f, GetScreenHeight() / 0.1));
			coords.emplace_back(Vec2f((float)GetScreenWidth() / 1.3, GetScreenHeight() / 1.2), Vec2f(0.f, GetScreenHeight() / 0.1));
			coords.emplace_back(Vec2f((float)GetScreenWidth() / 0.7, GetScreenHeight() / 1), Vec2f(0.f, GetScreenHeight() / 0.1));
			coords.emplace_back(Vec2f((float)GetScreenWidth() / 0.47, GetScreenHeight() / 1.15), Vec2f(0.f, GetScreenHeight() / 0.1));
			coords.emplace_back(Vec2f((float)GetScreenWidth() / 0.35, GetScreenWidth() / 1.3), Vec2f(0.f, GetScreenHeight() / 0.1));
		}

		void spawnEnemy(int index)
		{
			switch(index)
			{
				case 0: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", coords[0].first, coords[0].second, "hunter/1.mp3")); break;
				case 1: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", coords[1].first, coords[1].second, "hunter/2.mp3")); break;
				case 2: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", coords[2].first, coords[2].second, "hunter/3.mp3")); break;
				case 3: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", coords[3].first, coords[3].second, "hunter/4.mp3")); break;
				case 4: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", coords[4].first, coords[4].second, "hunter/5.mp3")); break;
			}

			enemies.back()->resize();
			enemies.back()->moveTowardsTarget();
		}

		void update() override
		{
			Core::update();

			if(screenResized)
				resizeImages();

			// sound effect for current enemy killed
			for(auto& obj : enemies)
			{
				if(obj->checkHit(currentClick))
				{
					audio.playSound(obj->sound);


					// right here kill the enemy
				}
			}

			for(auto& enemy : enemies)
			{
				enemy->moveTowardsTarget();
			}

			background.draw();
			car.draw();

			for(auto& enemy : enemies)
			{
				enemy->draw();
			}

		}

		void resizeImages()
		{
			background.resizeImage(Vec2f(GetScreenWidth(), GetScreenHeight()));
			car.resizeImage(Vec2f((float)GetScreenWidth() / 5, (float)GetScreenHeight() / 5));

			for(auto& enemy : enemies)
			{
				enemy->resize();
			}

		}

	private:
		Img background, car;
		std::vector<std::unique_ptr<Enemy>> enemies;

		// pair of position and target
		std::vector<std::pair<Vec2f, Vec2f>> coords;

};

int main(int argc, char** agrv)
{
	Hunter h;
	h.start();
	return 0;
}

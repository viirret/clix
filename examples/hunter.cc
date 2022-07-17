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
			speed = Vec2f(1.0f, 1.0f);

			// id of the Object
			id = "enemy";
		}

		std::string sound;

		void resize()
		{
			resizeImage(Vec2f((float)GetScreenWidth() / 20, (float)GetScreenWidth() / 20));
		}

		void move()
		{
			target = Vec2f(0, 200);
			moveTowardsTarget();
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
			resizeImages();

			// creating enemies
			for(size_t i = 0; i < 5; i++)
			{
				switch(i)
				{
					// TODO add all enemies
					case 0: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", Vec2f(0, 0), Vec2f(1, 0), "hunter/1.mp3")); break;
					case 1: enemies.push_back(std::make_unique<Enemy>("hunter/d2.png", Vec2f(100, 100), Vec2f(500, 500), "hunter/2.mp3")); break;
				}
			}

			spawnEnemy(0);
		}

		void spawnEnemy(int index)
		{
			//FIXME
			//Enemy n = enemies.at(index); n.move();
			
			enemies.at(index)->move();
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


			background.draw();
			car.draw();

			for(auto& enemy : enemies)
			{
				enemy->draw();
			}

		}

		void resizeEnemy(int index)
		{
			enemies[index]->resizeImage(Vec2f((float)GetScreenWidth() / 20, (float)GetScreenWidth() / 20));
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

};

int main(int argc, char** agrv)
{
	Hunter h;
	h.start();
	return 0;
}

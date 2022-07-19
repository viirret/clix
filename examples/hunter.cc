#include "../clix/Core.hh"
#include "../clix/Object.hh"
#include "../clix/Image.hh"
#include "../clix/Entity.hh"
#include "../clix/Controls.cc"

class Enemy : public Entity
{
	public:
		Enemy(std::string path, Vec2f position, std::string sound) : Entity(path, position), sound(sound)
		{
			// speed of Entity
			speed = Vec2f(0.f, 0.1f);

			// id of the Object
			id = "enemy";

			// same target for all enemies
			target = Vec2f(0.1f, GetScreenHeight() / 0.1);
		}

		std::string sound;

		void resize()
		{
			resizeImage(Vec2f((float)GetScreenWidth() / 20, (float)GetScreenWidth() / 20));
		}

};

class Gun : public Img
{
	public:
		Gun() : Img("hunter/shooter3.png", Vec2f((float)GetScreenWidth() / 0.79, (float)GetScreenHeight() / 0.54))
		{
		}

		int state;

		void update()
		{
			// gun controller logic
			if(Controls::up() && !Controls::down() && !Controls::left() && !Controls::right())
				state = 0;
			else if(Controls::left() && !Controls::down() && !Controls::right() && !Controls::up())
				state = 1;
			else if(Controls::right() && !Controls::down() && !Controls::up() && !Controls::left())
				state = 2;
			else if(Controls::up() && Controls::left() && !Controls::right() && !Controls::down())
				state = 3;
			else if(Controls::up() && Controls::right() && !Controls::left() && !Controls::down())
				state = 4;
			else
				state = -1;

			switch(state)
			{
				case 0: changeTexture("hunter/shooter3.png"); break;
				case 1: changeTexture("hunter/shooter1.png"); break;
				case 2: changeTexture("hunter/shooter5.png"); break;
				case 3: changeTexture("hunter/shooter2.png"); break;
				case 4: changeTexture("hunter/shooter4.png"); break;
				case -1: return;
			}
			resize();
		}

		void resize()
		{
			resizeImage(Vec2f((float)GetScreenWidth() / 16, (float)GetScreenWidth() / 16));
		}

};

class Hunter : public Core
{
	public:
		Hunter() 
			: 	Core(), 
				background("hunter/village.png"), 
				car("hunter/car.png", Vec2f((float)GetScreenWidth() / 0.8f, (float)GetScreenHeight() / 0.5f)),
				gun()
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
			positions.push_back(Vec2f((float)GetScreenWidth() / 10, GetScreenHeight() / 0.9));
			positions.push_back(Vec2f((float)GetScreenWidth() / 1.3, GetScreenHeight() / 1.2));
			positions.push_back(Vec2f((float)GetScreenWidth() / 0.7, GetScreenHeight() / 1));
			positions.push_back(Vec2f((float)GetScreenWidth() / 0.47, GetScreenHeight() / 1.15));
			positions.push_back(Vec2f((float)GetScreenWidth() / 0.35, GetScreenWidth() / 1.3));
		}

		void spawnEnemy(int index)
		{
			switch(index)
			{
				case 0: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", positions[0], "hunter/1.mp3")); break;
				case 1: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", positions[1], "hunter/2.mp3")); break;
				case 2: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", positions[2], "hunter/3.mp3")); break;
				case 3: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", positions[3], "hunter/4.mp3")); break;
				case 4: enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", positions[4], "hunter/5.mp3")); break;
			}

			enemies.back()->resize();
			enemies.back()->moveTowardsTarget();
		}

		void shooting()
		{
			if(Controls::space())
			{

			}
		}

		void update() override
		{
			Core::update();

			if(screenResized)
				resizeImages();

			gun.update();

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


			// main drawing
			background.draw();
			car.draw();
			gun.draw();

			for(auto& enemy : enemies)
			{
				enemy->draw();
			}

		}

		void resizeImages()
		{
			background.resizeImage(Vec2f(GetScreenWidth(), GetScreenHeight()));
			car.resizeImage(Vec2f((float)GetScreenWidth() / 5, (float)GetScreenHeight() / 5));
			gun.resize();

			for(auto& enemy : enemies)
			{
				enemy->resize();
			}
		}

	private:
		Img background, car;
		std::vector<std::unique_ptr<Enemy>> enemies;

		// pair of position and target
		std::vector<Vec2f> positions;

		Gun gun;

};

int main(int argc, char** agrv)
{
	Hunter h;
	h.start();
	return 0;
}

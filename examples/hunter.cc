#include "../clix/Core.hh"
#include "../clix/Object.hh"
#include "../clix/Image.hh"
#include "../clix/Entity.hh"
#include "../clix/Controls.cc"

class Enemy : public Entity
{
	public:
		Enemy(std::string path, Vec2f position, std::string sound, int pos) : Entity(path, position), sound(sound), pos(pos)
		{
			// speed of Entity
			speed = Vec2f(0.f, 0.1f);

			// id of the Object
			id = "enemy";

			// same target for all enemies
			target = Vec2f(0.1f, GetScreenHeight() / 0.1);
		}

		std::string sound;
		int pos;
		bool alive = true;

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
			state = 3;
		}

		int state;

		void update()
		{
			int newState = -1;

			// gun controller logic
			if(Controls::leftOnly())
				newState = 1;
			else if(Controls::up() && Controls::left() && !Controls::right() && !Controls::down())
				newState = 2;
			else if(Controls::upOnly())
				newState = 3;
			else if(Controls::up() && Controls::right() && !Controls::left() && !Controls::down())
				newState = 4;
			else if(Controls::rightOnly())
				newState = 5;

			// only change texture if button is pressed
			if(newState != -1)
			{
				state = newState;
				changeTexture("hunter/shooter" + std::to_string(state) + ".png");
				resize();
			}
		}

		void resize()
		{
			resizeImage(Vec2f((float)GetScreenWidth() / 16, (float)GetScreenWidth() / 16));
		}

};

class Fire : public Img
{
	public:
		Fire()
		{
			position = Vec2f(GetScreenWidth() / 0.8, GetScreenHeight() / 0.5);
		}

		bool render;

		void execute(int pos)
		{
			changeTexture("hunter/shoot" + std::to_string(pos) + ".png");
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
				gun(),
				fire()
		{
			createSpawns();

			spawnAll();

			resizeImages();
		}

		void spawnAll()
		{
			for(int i = 1; i < 6; i++)
				spawnEnemy(i);
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
			enemies.push_back(std::make_unique<Enemy>("hunter/d1.png", positions[index - 1], "hunter/" + std::to_string(index) + ".mp3", index));
			enemies.back()->resize();
		}

		void shooting()
		{
			if(Controls::spaceOnce())
			{
				printf("space pressed\n");
				audio.playSound("gunshow.mp3");
				fire.execute(gun.state);
				fire.render = true;

				for(auto& enemy : enemies)
				{
					if(enemy->pos == gun.state)
					{
						if(enemy->alive)
						{
							audio.playSound(enemy->sound);
							enemy->alive = false;
						}
					}
				}
			}
		}

		void update() override
		{
			Core::update();

			if(screenResized)
			{
				printf("Screen resized\n");
				resizeImages();
			}

			shooting();

			for(auto& enemy : enemies)
			{
				enemy->moveTowardsTarget();
			}

			gun.update();


			// main drawing
			background.draw();
			car.draw();
			gun.draw();

			if(fire.render)
				fire.draw();

			fire.render = false;

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
		Fire fire;

};

int main(int argc, char** agrv)
{
	Hunter h;
	h.start();
	return 0;
}

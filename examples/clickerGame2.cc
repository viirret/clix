#include "../clix/Core.hh"
#include "../clix/Crosshair.hh"
#include "../clix/Player.hh"

class Enemy : public Img
{
	public:
		Enemy(std::string path, Vec2f position) : Img(path, position)
		{
			type = Object::Type::enemy;
		}
};

class Ammo : public Img
{
	public:
		Ammo(std::string path, Vec2f position) : Img(path, position)
		{
			type = Object::Type::ammo;
		}
};

class clickerGame2 : public Core
{
	public:
		clickerGame2() : 
					Core(),
				  	crosshair(),
				  	player(),
					resetButton((Config::ASSETSPATH + "playagain.png").c_str(), Vec2f(1, 1)) // add resetbutton for game over
		{
			images.push_back(std::make_unique<Enemy>("arch.png", Vec2f(500, 500)));
		}

		void update() override
		{
			Core::update();
			crosshair.updateCrosshair(mousePosition);

			// setup for game over
			if(player.gun.getCapacity() <= 0)
				isGameOver = true;

			if(isGameOver)
				gameOver();

			// render images
			for(auto& obj : images)
				obj->draw();

			if(IsMouseButtonPressed(0))
			{
				if(player.gun.getCapacity() > 0)
				{
					audio.playSound("gunshow.mp3");

					// update mag size
					player.gun.fire();
				}
			}

			/*
			// GAMEPLAY LOGIC	
			for(size_t i = 0; i < (size_t)images.size(); i++)
			{
				// if enemy is clicked
				if(images[i]->checkHit(currentClick))
				{
					printf("object hit\n");
					switch(images[i]->type)
					{
						case Object::Type::enemy: 
							// update amount of killed enemies
							killedEnemies++;
							killedString = std::to_string(killedEnemies);
							break;
						case Object::Type::ammo:
							player.gun.restock();
							break;
						case Object::Type::object: break;
					}
					
					// delete clicked element
					//images.erase(images.begin() + i);

					// add new enemy 
					//spawnEnemyRandom("arch.png");

					//images[0]->setRandomTarget();
				}
			}

			// OBJECT MOVEMENT LOGIC
			for(auto& obj : images)
			{
				switch(obj->type)
				{
					case Object::Type::enemy: 
						obj->moveTowardsTarget();
						break;

					case Object::Type::ammo: break;
					case Object::Type::object: break;
				}
			}
			*/

			for(auto& obj : images)
			{
				obj->moveTowardsTarget();
			}
	
			crosshair.draw();

			// update ammo count
			std::string ammoText = player.gun.capacity + " / " + player.gun.magazineSize;
			DrawText(ammoText.c_str(), GetScreenWidth() - GetScreenWidth() / 4, GetScreenHeight() - GetScreenHeight() / 10, 30, BLUE);

			// update killed enemies count
			DrawText(killedString.c_str(), GetScreenWidth() / 20, GetScreenHeight() / 20, 30, BLACK);
	
		}

		void gameOver()
		{
			// reset current click to (0, 0) to avoid instant hit
			if(!currentHitChanged)
			{
				currentClick = Vec2f();
				currentHitChanged = true;
			}

			// render things
			DrawText("clickerGame Over!", GetScreenWidth() / 3, GetScreenHeight() / 3, 40, BLACK);
			resetButton.draw(WHITE);

			// is resetbutton is clicked start a new game
			if(resetButton.checkHit(currentClick))
			{
				currentHitChanged = false;
				isGameOver = false;
				resetGame();
			}
		}

		void resetGame()
		{
			killedEnemies = 0;
			killedString = std::to_string(killedEnemies);
			player.gun.restock();
		}

	private:
		// instances of other classes
		Crosshair crosshair;
		Player player;
		Object resetButton;

		// variables for gameplay
		int killedEnemies;
		std::string killedString;
		bool isGameOver = false;
		bool currentHitChanged = false;
};

int main(int argc, char** argv)
{
	clickerGame2 c;
	c.start();
	return 0;
}

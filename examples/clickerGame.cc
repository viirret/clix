#include "../clix/Core.hh"
#include "../clix/Crosshair.hh"
#include "../clix/Player.hh"
#include "../clix/Entity.hh"

class Enemy : public Entity
{
	public:
		Enemy(std::string path, Vec2f position, Vec2f speed, Vec2f target) : Entity(path, position, speed, target)
		{
			this->id = "enemy";
		}

};

class Ammo : public Entity
{
	public:
		Ammo(std::string path, Vec2f position, Vec2f speed, Vec2f target) : Entity(path, position, speed, target)
		{
			this->id = "ammo";
		}
};

class clickerGame : public Core
{
	public:
		clickerGame() : 
					Core(),
				  	crosshair(),
				  	player(),
					resetButton((Config::ASSETSPATH + "playagain.png").c_str(), Vec2f(1, 1)) // add resetbutton for game over
		{
			enemies.push_back(std::make_unique<Enemy>("arch.png", Vec2f(500, 500), Vec2f(1.1f, 0.1f), Vec2f(600, 600)));
			enemies.push_back(std::make_unique<Ammo>("ammo.png", Vec2f(100, 100), Vec2f(1.f, 1.f), Vec2f(100, 100)));

			printf("TYPE: %s\n", enemies[0]->id.c_str());
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
			for(auto& obj : enemies)
				obj->draw();

			if(IsMouseButtonPressed(0))
			{
				if(player.gun.getCapacity() > 0)
				{
					audio.playSound("mosin.wav");

					// update mag size
					player.gun.fire();
				}
			}

			for(auto& obj : enemies)
			{
				obj->moveTowardsTarget();
			}

			for(auto& obj : enemies)
			{
				if(obj->checkHit(currentClick))
				{
					if(obj->id == "enemy")
					{
						killedEnemies++;
						killedString = std::to_string(killedEnemies);
					}
					if(obj->id == "ammo")
					{
						player.gun.restock();
					}
				}
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
		Img resetButton;

		// variables for gameplay
		int killedEnemies;
		std::string killedString;
		bool isGameOver = false;
		bool currentHitChanged = false;

		std::vector<std::unique_ptr<Entity>> enemies;
};

int main(int argc, char** argv)
{
	clickerGame c;
	c.start();
	return 0;
}

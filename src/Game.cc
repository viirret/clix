#include "Game.hh"

Game::Game() 
	: 	Core(),			// start core
		crosshair(),	// implement default crosshair
		player(),		// add player
		resetButton((glb::assetsPath + "playagain.png").c_str(), Vec2f(1, 1)) // add resetbutton for game over
{
	resetGame();
	spawnEnemyRandom("arch.png");
}

void Game::update()
{
	Core::update();
	updateGame();
	draw();
}

void Game::updateGame()
{
	// setup for game over
	if(player.gun.getCapacity() <= 0)
		isGameOver = true;

	if(isGameOver)
		gameOver();

	// update crosshair
	crosshair.updateCrosshair(mousePosition);

	if(IsMouseButtonPressed(0))
	{
		if(player.gun.getCapacity() > 0)
		{
			audio.playSound("gunshow.mp3");

			// update mag size
			player.gun.fire();
		}
	}

	// GAMEPLAY LOGIC	
	for(size_t i = 0; i < (size_t)objects.size(); i++)
	{
		// if enemy is clicked
		if(objects[i]->checkHit(currentClick))
		{
			// redefine currenthit
			 currentClick = Vec2f();

			switch(objects[i]->type)
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
			objects.erase(objects.begin() + i);

			// add new enemy 
			spawnEnemyRandom("arch.png");

			objects[0]->setRandomTarget();
		}
	}

	// OBJECT MOVEMENT LOGIC
	for(auto& obj : objects)
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
}

void Game::gameOver() 
{
	// reset current click to (0, 0) to avoid instant hit
	if(!currentHitChanged)
	{
		currentClick = Vec2f();
		currentHitChanged = true;
	}

	// render things
	DrawText("Game Over!", GetScreenWidth() / 3, GetScreenHeight() / 3, 40, BLACK);
	resetButton.draw(WHITE);

	// is resetbutton is clicked start a new game
	if(resetButton.checkHit(currentClick))
	{
		resetGame();
		isGameOver = false;
	}
}

void Game::resetGame()
{
	killedEnemies = 0;
	killedString = std::to_string(killedEnemies);
	player.gun.restock();
}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	crosshair.draw(WHITE);

	// render enemies
	for(auto& obj : objects)
		obj->draw(WHITE);

	// update ammo count
	std::string ammoText = player.gun.capacity + " / " + player.gun.magazineSize;
	DrawText(ammoText.c_str(), GetScreenWidth() - GetScreenWidth() / 4, GetScreenHeight() - GetScreenHeight() / 10, 30, BLUE);

	// update killed enemies count
	DrawText(killedString.c_str(), GetScreenWidth() / 20, GetScreenHeight() / 20, 30, BLACK);

	EndDrawing();
}

int main(int argc, char** argv)
{
	Game g;

	while(!g.close)
		g.update();

	return 0;
}



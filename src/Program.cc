#include "Program.hh"

template<typename T> T randomSpawn(T from, T to)
{
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<T> dist(from, to);
	return dist(generator);
}

Program::Program() : 
					initializer(), 
					crosshair(),
					player(),
					audio(),
					resetButton((glb::assetsPath + "playagain.png").c_str(), 1, 1)
					// has to be at least 1, 1 because Vec2f(); is x = 0, y = 0
{
	resetGame();
	setSpawns();
	spawnEnemyRandom("arch.png");
	//spawnAmmo("ammo.png", 1);
	objects[0]->setTarget(Vec2f(100.0f, 100.0f));
}

Program::~Program()
{
}

// set variables for new game
void Program::resetGame()
{
	killedEnemies = 0;
	killedString = std::to_string(killedEnemies);
	currentHitChanged = false;
	player.gun.restock();
}

void Program::setSpawns()
{
	// set a few example spawnpoints
	spawns.push_back(Vec2f((float)GetScreenWidth() / 2, (float)GetScreenWidth()) / 2);
	spawns.push_back(Vec2f((float)GetScreenWidth() / 3, (float)GetScreenWidth()) / 3);
	spawns.push_back(Vec2f((float)GetScreenWidth() / 4, (float)GetScreenWidth()) / 4);
}

void Program::run()
{
	updateGame();
	objectMovement();
	events();
	draw();
}

void Program::objectMovement()
{
	objects[0]->moveTowardsTarget();
}

void Program::updateGame()
{
	// setup for game over
	if(player.gun.getCapacity() <= 0)
		gameIsOver = true;

	if(gameIsOver)
		gameOver();

	// update crosshair
	crosshair.updateCrosshair(mousePosition);

	// loop all existing objects
	for(size_t i = 0; i < (size_t)objects.size(); i++)
	{
		// if enemy is clicked
		if(objects[i]->checkHit(currenthit))
		{
			// redefine currenthit
			currenthit = Vec2f();

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
			objects[0]->setTarget(Vec2f((float)GetScreenWidth() / 3, (float)GetScreenHeight() / 2));
		}
	}

	// update ammo
	std::string ammoText = player.gun.capacity + " / " + player.gun.magazineSize;
	DrawText(ammoText.c_str(), GetScreenWidth() - GetScreenWidth() / 4, GetScreenHeight() - GetScreenHeight() / 10, 30, BLUE);

	// update killed enemies count
	DrawText(killedString.c_str(), GetScreenWidth() / 20, GetScreenHeight() / 20, 30, BLACK);
} 

void Program::spawnEnemyRandom(std::string texture)
{
	// get new random spawn and add enemy there
	int rnd = randomSpawn(0, (int)spawns.size() - 1);
	objects.push_back(std::make_unique<Enemy>((glb::assetsPath + texture).c_str(), spawns.at(rnd).x, spawns.at(rnd).y));
}

void Program::spawnEnemy(std::string texture, int index)
{
	objects.push_back(std::make_unique<Enemy>((glb::assetsPath + texture).c_str(), spawns.at(index).x, spawns.at(index).y));
}

void Program::spawnAmmo(std::string texture, int index)
{
	objects.push_back(std::make_unique<Ammo>((glb::assetsPath + texture).c_str(), spawns.at(index).x, spawns.at(index).y));
}

void Program::events() 
{
	// default raylib closing
	if(WindowShouldClose())
		close = true;

	// always track mouse position
	mousePosition = Vec2f(GetMousePosition().x, GetMousePosition().y);

	// get vector2 on mouse position when clicked
	if(IsMouseButtonPressed(0))
	{
		currenthit = mousePosition;

		if(player.gun.getCapacity() > 0)
		{
			audio.playSound("gunshow.mp3");

			// update mag size
			player.gun.fire();
		}
	}
}

void Program::gameOver()
{
	// reset current click to (0, 0) to avoid instant hit
	if(!currentHitChanged)
	{
		currenthit = Vec2f();
		currentHitChanged = true;
	}

	// render things
	DrawText("Game Over!", GetScreenWidth() / 3, GetScreenHeight() / 3, 40, BLACK);
	resetButton.draw(WHITE);

	// is resetbutton is clicked start a new game
	if(resetButton.checkHit(currenthit))
	{
		resetGame();
		gameIsOver = false;
	}
}

void Program::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	// render enemies
	for(auto& obj : objects)
		obj->draw(WHITE);

	// draw crosshair
	DrawTexture(crosshair.texture, crosshair.x, crosshair.y, WHITE);
	EndDrawing();
}


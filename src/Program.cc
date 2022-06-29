#include "Program.hh"

Program::Program() : 
					initializer(), 
					crosshair(),
					player(),
					audio(),
					resetButton((glb::assetsPath + "playagain.png").c_str(), Vec2f(1, 1))
					// has to be at least 1, 1 because Vec2f(); is x = 0, y = 0
{
	resetGame();
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

void Program::run()
{
	// updating main game logic
	updateGame();

	// updating objects movement
	objectMovement();

	// event handling
	events();

	// updating raylib drawing
	draw();
}

void Program::gameLogic()
{
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

			objects[0]->setRandomTarget();
		}
	}


}

void Program::objectMovement()
{
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

void Program::updateGame()
{
	// setup for game over
	if(player.gun.getCapacity() <= 0)
		gameIsOver = true;

	if(gameIsOver)
		gameOver();

	// update crosshair
	crosshair.updateCrosshair(mousePosition);

	gameLogic();

	// update ammo
	std::string ammoText = player.gun.capacity + " / " + player.gun.magazineSize;
	DrawText(ammoText.c_str(), GetScreenWidth() - GetScreenWidth() / 4, GetScreenHeight() - GetScreenHeight() / 10, 30, BLUE);

	// update killed enemies count
	DrawText(killedString.c_str(), GetScreenWidth() / 20, GetScreenHeight() / 20, 30, BLACK);
} 

Vec2f Program::getRandomSpawn(Texture texture)
{
	float a = rnd<float>::randomValue(0.0f, (float)GetScreenWidth() - texture.width);
	float b = rnd<float>::randomValue(0.0f, (float)GetScreenHeight() - texture.height);
	return Vec2f(a, b);
}

void Program::spawnEnemyRandom(std::string texture)
{
	auto obj = std::make_unique<Object>((glb::assetsPath + texture).c_str());

	// we need textures size for random position
	obj->setPosition(getRandomSpawn(obj->getTexture()));
	obj->setType(Object::Type::enemy);
	objects.push_back(std::move(obj));
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


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
					player()
{
	setVariables();
	objects.push_back(std::make_unique<Object>("../assets/arch.png", GetScreenWidth() / 3, GetScreenHeight() / 3));
}

Program::~Program()
{
}

void Program::setVariables()
{
	killedEnemies = 0;
	killedString = std::to_string(killedEnemies);
	setSpawns();
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
	events();
	draw();
}

void Program::updateGame()
{
	// update crosshair
	//crosshair.updateCrosshair(mousePosition);

	// loop all existing enemies
	for(size_t i = 0; i < (size_t)objects.size(); i++)
	{
		// if enemy is clicked
		if(objects[i]->checkHit(currenthit))
		{
			// redefine currenthit
			currenthit.x = 0;
			currenthit.y = 0;

			// delete clicked element
			objects.erase(objects.begin() + i);

			// get new random spawn and add enemy there
			int rnd = randomSpawn(0, (int)spawns.size() - 1);
			objects.push_back(std::make_unique<Object>("../assets/arch.png", spawns.at(rnd).x, spawns.at(rnd).y));

			// update amount of killed enemies
			killedEnemies++;
			killedString = std::to_string(killedEnemies);
		}
	}

	// update ammo
	std::string ammoText = player.gun.capacity + " / " + player.gun.magazineSize;
	DrawText(ammoText.c_str(), GetScreenWidth() - GetScreenWidth() / 4, GetScreenHeight() - GetScreenHeight() / 10, 30, BLUE);

	// update killed enemies count
	DrawText(killedString.c_str(), GetScreenWidth() / 20, GetScreenHeight() / 20, 30, BLACK);
} 

void Program::events() 
{
	// default raylib closing
	if(WindowShouldClose())
		close = true;

	// always track mouse position
	mousePosition = GetMousePosition();

	// get vector2 on mouse position when clicked
	if(IsMouseButtonPressed(0))
	{
		currenthit = mousePosition;

		// update mag size
		player.gun.fire();
	}
}

void Program::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	// render enemies
	for(auto& obj : objects)
		DrawTexture(obj->texture, obj->x, obj->y, WHITE);

	// draw crosshair
	DrawTexture(crosshair.texture, crosshair.x, crosshair.y, WHITE);
	EndDrawing();
}


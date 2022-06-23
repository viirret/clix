#include "Program.hh"

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
	
	// delete elements when clicking
	for(size_t i = 0; i < (size_t)objects.size(); i++)
	{
		if(objects[i]->checkHit(currenthit))
		{
			objects.erase(objects.begin() + i);
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


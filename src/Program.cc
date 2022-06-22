#include "Program.hh"

Program::Program() : 
					initializer(), 
					//arch("../assets/arch.png", GetScreenWidth() / 2, GetScreenHeight() / 2), 
					crosshair()
{

	objects.push_back(new Object("../assets/arch.png", GetScreenWidth() / 3, GetScreenHeight() / 3));
}

Program::~Program()
{
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
	for(int i = 0; i < (int)objects.size(); i++)
		if(objects[i]->checkHit(currenthit))
			objects.erase(objects.begin() + i);
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
		currenthit = mousePosition;
}

void Program::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	for(auto& obj : objects)
		DrawTexture(obj->texture, obj->x, obj->y, WHITE);

	// draw crosshair
	DrawTexture(crosshair.texture, crosshair.x, crosshair.y, WHITE);
	EndDrawing();
}


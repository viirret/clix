#include "Program.hh"

Program::Program() : initializer(), player("../assets/arch.png", GetScreenWidth() / 2, GetScreenHeight() / 2)
{
}

Program::~Program()
{
}

void Program::run()
{
	draw();
	movement();
	events();
}

void Program::events()
{
	// default raylib closing
	if(WindowShouldClose())
		close = true;

	//printf("X = %d\n", GetMouseX());
	//printf("Y = %d\n", GetMouseY());
}

void Program::movement()
{
	/*
	if(Controls::jump())
	{
		player.posHeight--;
	}
	*/
}

void Program::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	// draw player
	DrawTexture(player.texture, player.posWidth, player.posHeight, WHITE);
	EndDrawing();
}

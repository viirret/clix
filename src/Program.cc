#include "Program.hh"

Program::Program()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "");
	player.setTexture("../assets/arch.png");
}

Program::~Program()
{
	CloseWindow();
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
}

void Program::movement()
{
	if(Controls::jump())
	{
		player.posHeight--;
	}
}

void Program::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	// draw player
	DrawTexture(player.texture, player.posWidth, player.posHeight, WHITE);
	EndDrawing();
}

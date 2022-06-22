#include "Program.hh"

Program::Program() : initializer(), arch("../assets/arch.png", GetScreenWidth() / 2, GetScreenHeight() / 2)
{

}

Program::~Program()
{
}

void Program::run()
{
	events();
	draw();
}

void Program::events()
{
	// default raylib closing
	if(WindowShouldClose())
		close = true;

	// get vector2 on mouse position when clicked
	if(IsMouseButtonPressed(0))
		currenthit = GetMousePosition();

	if(arch.checkHit(currenthit))
	{
		printf("hit\n");
	}
}

void Program::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	// draw player
	DrawTexture(arch.texture, arch.posX, arch.posY, WHITE);
	EndDrawing();
}

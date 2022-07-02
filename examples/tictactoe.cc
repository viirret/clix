#include "tictactoe.hh"

tictactoe::tictactoe() : Core()
{
	std::vector<Vec2f> squares;

	float space = 10.f;

	Vec2f squareSize = Vec2f((float)GetScreenWidth() / 3 - space, (float)GetScreenHeight() / 3 - space);

	int line = 0;
	int column = 0;
	for(size_t i = 0; i < 9; ++i)
	{
		squares.push_back(Vec2f(1, 1));
	}
}

void tictactoe::update()
{
	Core::update();

	BeginDrawing();

	DrawRectangle(10, 20, 20, 20, BLUE); 

	EndDrawing();
}

int main(int argc, char** argv)
{
	tictactoe t;

	while(!t.close)
		t.update();
	
	return 0;
}


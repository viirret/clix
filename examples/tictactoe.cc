#include "../clix/Core.hh"

class tictactoe : public Core
{
	public:
		tictactoe() : Core()
		{
			squareSize = Vec2f((float)GetScreenWidth() / 3 - spacex, (float)GetScreenHeight() / 3 - spacey);

			for(size_t i = 0; i < 3; ++i)
			{
				for(size_t j = 0; j < 3; ++j)
				{
					squares.push_back(Vec2f(squareSize.x * line + spacex, squareSize.y * column + spacey));
					column++;
				}
				column = 0;
				line++;
			}
		}

		void update()
		{
			Core::update();

			BeginDrawing();

			for(auto& sqr : squares)
			{
				drawRectangle(Vec2f(sqr.x + spacex, sqr.y + spacey), Vec2f(squareSize.x - spacex, squareSize.y - spacey), BLUE);
			}

			EndDrawing();
		}

	private:
	
		Vec2f squareSize;
		std::vector<Vec2f> squares;
		float spacex = (float)GetScreenWidth() / 30;
		float spacey = (float)GetScreenHeight() / 30;
		int line = 0;
		int column = 0;
};

int main(int argc, char** argv)
{
	tictactoe t;

	while(!t.close)
		t.update();
	
	return 0;
}


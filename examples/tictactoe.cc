#include "../clix/Core.hh"

Vec2f squareSize;

class Square
{
	public:
		enum class Owner
		{
			p1,
			p2,
			free
		};

		Owner owner;

		Square(int x, int y, Vec2f location) : x(x), y(y), location(location) 
		{
			max = Vec2f(location.x + squareSize.x, location.y + squareSize.y);	
			owner = Owner::free;
		}

		int x, y;
		Vec2f location;
		Vec2f max;
		Color color;
};

class tictactoe : public Core
{
	public:
		tictactoe() : Core()
		{
			squareSize = Vec2f((float)GetScreenWidth() / 3 - spacex, (float)GetScreenHeight() / 3 - spacey);

			// create squares
			for(size_t i = 0; i < 3; ++i)
			{
				for(size_t j = 0; j < 3; ++j)
				{
					squares.push_back(Square(i, j, Vec2f(squareSize.x * line + spacex, squareSize.y * column + spacey)));
					column++;
				}
				column = 0;
				line++;
			}
		}

		// start the program, TODO implement in base class
		void start()
		{
			while(!close)
				update();
		}

		void updateGame()
		{
			// main game logic
			for(auto& sqr : squares)
			{
				if(isClicked(sqr.location, sqr.max))
				{
					// TODO somehow get rid of this sentence
					currentClick = Vec2f(0, 0);
					
					sqr.owner = p1Turn ? Square::Owner::p1 : Square::Owner::p2;
					p1Turn = !p1Turn;
				}
			}
		}

		void update()
		{
			Core::update();

			BeginDrawing();

			updateGame();

			// determine square colors
			for(auto& sqr : squares)
			{
				switch(sqr.owner)
				{
					case Square::Owner::free: sqr.color = BLUE; break;
					case Square::Owner::p1: sqr.color = RED; break;
					case Square::Owner::p2: sqr.color = WHITE; break;
				}
			}

			// render squares
			for(auto& sqr : squares)
			{
				drawRectangle(Vec2f(sqr.location.x + spacex, sqr.location.y + spacey), Vec2f(squareSize.x - spacex, squareSize.y - spacey), sqr.color);
			}

			EndDrawing();
		}

	private:

		bool p1Turn = true;
		float spacex = (float)GetScreenWidth() / 30;
		float spacey = (float)GetScreenHeight() / 30;
		int line = 0;
		int column = 0;
		std::vector<Square> squares;
};

int main(int argc, char** argv)
{
	tictactoe t;
	t.start();
	
	return 0;
}


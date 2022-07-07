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
		
		// constructor for normal squares
		Square(int x, int y, Vec2f location) : x(x), y(y), location(location) 
		{
			max = Vec2f(location.x + squareSize.x, location.y + squareSize.y);	
			owner = Owner::free;
		}

		// constructor for update button
		Square(Vec2f location, Vec2f size) : location(location)
		{
			max = Vec2f(location.x + size.x, location.y + size.y);
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
			createSquares();
		}

		void createSquares()
		{
			squares.clear();
			line = 0;
			column = 0;

			for(size_t i = 0; i < 3; ++i)
			{
				for(size_t j = 0; j < 3; ++j)
				{
					squares.push_back(Square(i, j, Vec2f(squareSize.x * line + spacex, squareSize.y * column + spacey)));
					line++;
				}
				line = 0;
				column++;
			}
		}

		// start the program, TODO implement in base class
		void start()
		{
			while(!close)
				update();
		}

		Square::Owner checkRow(Square s1, Square s2, Square s3)
		{
			if(s1.owner == s2.owner && s2.owner == s3.owner)
				return s1.owner;
			return Square::Owner::free;
		}

		void announceWinner(Square square)
		{
			square.owner == Square::Owner::p1 ? printf("p1 won\n") : printf("p2 won\n");
		}

		void update()
		{
			Core::update();

			// check clicks for each square
			for(auto& sqr : squares)
			{
				// only allow clicks on unclicked squares
				if(sqr.owner == Square::Owner::free)
				{
					if(isClicked(sqr.location, sqr.max))
					{
						sqr.owner = p1Turn ? Square::Owner::p1 : Square::Owner::p2;
						p1Turn = !p1Turn;
					}
				}
			}

			// check if either player has won the game
			determineWinner();

			// check if updatebutton is pressed
			if(isClicked(updateButton.location, updateButton.max))
				createSquares();
			
			// determine square colors
			for(auto& sqr : squares)
			{
				switch(sqr.owner)
				{
					case Square::Owner::p1: sqr.color = RED; break;
					case Square::Owner::p2: sqr.color = BLUE; break;
					case Square::Owner::free: sqr.color = BROWN; break;
				}
			}

			BeginDrawing();

			// render squares
			for(auto& sqr : squares)
			{
				drawRectangle(Vec2f(sqr.location.x + spacex, sqr.location.y + spacey), Vec2f(squareSize.x - spacex, squareSize.y - spacey), sqr.color);
			}
			
			// draw updateButton
			drawRectangle(updateButton.location, Vec2f(20, 20), GREEN);

			EndDrawing();
		}

		void determineWinner()
		{
			// check straight lines
			for(size_t i = 0; i < (size_t)squares.size(); i++)
			{
				if(i == 0 || i == 3 || i == 6)
					if(checkRow(squares[i], squares[i + 1], squares[i + 2]) != Square::Owner::free)
						announceWinner(squares[i]);

				if(i == 0 || i == 1 || i == 2)
					if(checkRow(squares[i], squares[i + 3], squares[i + 6]) != Square::Owner::free)
						announceWinner(squares[i]);
			}

			// check crossing lines
			if(checkRow(squares[0], squares[4], squares[8]) != Square::Owner::free)
				announceWinner(squares[0]);
			if(checkRow(squares[2], squares[4], squares[6]) != Square::Owner::free)
				announceWinner(squares[2]);
		}

	private:
		bool p1Turn = true;
		float spacex = (float)GetScreenWidth() / 30;
		float spacey = (float)GetScreenHeight() / 30;
		int line, column;
		std::vector<Square> squares;
		Square updateButton = Square(Vec2f((float)GetScreenWidth() / 2 - 10, 3), Vec2f(20, 20));
};

int main(int argc, char** argv)
{
	tictactoe t;
	t.start();
	
	return 0;
}


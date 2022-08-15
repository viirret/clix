#include "../clix/Core.hh"
#include "../clix/Controls.hh"

#define bsx blockSize.x
#define bsy blockSize.y

// blockSize depends on screen's value
Vec2f blockSize;

bool hitTarget(Vec2f elem, Vec2f target)
{
	return elem.x + bsx > target.x && elem.x < target.x + bsx && elem.y < target.y + bsy && elem.y + bsy > target.y;
}

class Snake
{
	public:
		// reset snake to starting position
		void setSnake()
		{
			blocks.clear();

			// add the first block
			addBlock(Vec2f(rnd<float>::randomValue(GetScreenWidth() - bsx, 0), rnd<float>::randomValue(GetScreenHeight() - bsy, 0)));

			for(size_t i = 0; i < (size_t)initialAmount - 1; i++)
				addBlock(Vec2f(blocks.back()));

			snakeMoving = true;
		}

		// set the direction of the snake, snake cannot turn 180 degrees
		void setDirection()
		{
			if(Controls::up() && direction != 2) direction = 1;
			if(Controls::down() && direction != 1) direction = 2;
			if(Controls::left() && direction != 4) direction = 3;
			if(Controls::right() && direction != 3) direction = 4;
		}

		void move()
		{
			Vec2f oldBlock = blocks[0];

			// move the first block
			switch(direction)
			{
				case 1: blocks[0].y -= bsy; break;
				case 2: blocks[0].y += bsy; break;
				case 3: blocks[0].x -= bsx; break;
				case 4: blocks[0].x += bsx; break;
			}

			// move the other blocks
			for(size_t i = 1; i < (size_t)blocks.size(); i++)
			{
				Vec2f newBlock = blocks[i];
				blocks[i] = oldBlock;
				oldBlock = newBlock;
			}

			// snake goes over the edge
			if(blocks[0].x > GetScreenWidth())
				blocks[0].x = 0;

			if(blocks[0].y > GetScreenHeight())
				blocks[0].y = 0;

			if(blocks[0].x < 0)
				blocks[0].x = GetScreenWidth();

			if(blocks[0].y < 0)
				blocks[0].y = GetScreenHeight();
		}

		// check if snake hits the food from all directions
		bool checkFood(Vec2f t)
		{
			if(hitTarget(blocks[0], t))
			{
				addBlock(Vec2f(blocks.back()));
				return true;
			}
			return false;
		}

		// snake hits itself
		bool loseGame()
		{
			for(size_t i = 1; i < (size_t)blocks.size(); i++)
				if(hitTarget(blocks[0], blocks[i]))
					return true;
			return false;
		}

		void addBlock(Vec2f position)
		{
			blocks.push_back(position);
		}

		double speed = 2.0;
		int initialAmount = 3;
		bool snakeMoving = false;

		// colors of the snake
		Color color = RED;
		Color secondColor = BLACK;

		// the initial direction of the snake (1..4)
		int direction = 3;

		// vector containing snake parts
		std::vector<Vec2f> blocks;
};

class Game : public Core
{
	public:
		Game() : Core(), resetButton("play.png")
		{
			setFood();
		}

		void update() override
		{
			Core::update();

			if(s.snakeMoving)
			{
				// set controls
				s.setDirection();

				// snake movement
				if(mTimer > s.speed)
				{
					s.move();
					mTimer = 0;

					if(s.loseGame())
					{
						s.snakeMoving = false;
						return;
					}
				}
				mTimer += delta;

				// check if snake eats food
				if(s.checkFood(food))
					setFood();

				// render snake
				for(size_t i = 0; i < (size_t)s.blocks.size(); i++)
					drawRectangle(s.blocks[i], blockSize, i == 0 ? s.secondColor : s.color);

				// render food
				drawRectangle(food, blockSize, BLUE);
			}
			else
				endGame();
		
			if(screenResized)
				resize();
		}

		// spawn food in random position
		void setFood()
		{
			food = Vec2f(rnd<float>::randomValue(GetScreenWidth() - bsx, 0), rnd<float>::randomValue(GetScreenHeight() - bsy, 0));

			// food cannot spawn in snake
			for(auto& b : s.blocks)
				if(hitTarget(food, b))
					setFood();
		}

		void endGame()
		{
			resetButton.draw();

			// start new game if button is pressed
			if(resetButton.checkHit(currentClick))
				s.setSnake();
		}

		void resize()
		{
			blockSize = Vec2f((float)GetScreenHeight() / 20, (float)GetScreenHeight() / 20);
			resetButton.setPosition(Vec2f(1.f, 1.f));
		}

	private:
		Snake s;
		Vec2f food;
		double mTimer = 0;
		Img resetButton;
};

int main(int argc, char** argv)
{
	Game g;
	g.start();

	return 0;
}

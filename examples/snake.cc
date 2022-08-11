#include "../clix/Core.hh"
#include "../clix/Controls.hh"

#define bsx blockSize.x
#define bsy blockSize.y

// blockSize depends on screen's value
Vec2f blockSize;

class Snake
{
	public:
		Snake()
		{
			for(size_t i = 0; i < (size_t)initialAmount; i++)
				addBlock(Vec2f(i * bsx + GetScreenWidth(), (float)GetScreenHeight()));
		}

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
			for(size_t i = 0; i < (size_t)blocks.size(); i++)
			{
				if(i != 0)
				{
					Vec2f newBlock = blocks[i];
					blocks[i] = oldBlock;
					oldBlock = newBlock;
				}
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
			Vec2f hit = blocks[0];

			if(hit.x + bsx > t.x && hit.x < t.x + bsx && hit.y < t.y + bsy && hit.y + bsy > t.y)
			{
				addBlock(Vec2f(blocks.back()));
				return true;
			}
			return false;
		}

		bool loseGame()
		{
			for(size_t i = 0; i < (size_t)blocks.size(); i++)
			{
				if(i != 0)
				{
					Vec2f f = blocks[0];
					Vec2f l = blocks[i];

					if(f.x + bsx > l.x && f.x < l.x + bsx && f.y < l.y + bsy && f.y + bsy > l.y)
						return true;
				}
			}
			return false;
		}

		void addBlock(Vec2f position)
		{
			blocks.push_back(position);
		}

		double speed = 2.0;
		int size = 3;
		Color color = RED;
		Color secondColor = BLACK;
		int initialAmount = 3;

		// the initial direction of the snake (1..4)
		int direction = 3;

		std::vector<Vec2f> blocks;
};

class Game : public Core
{
	public:
		Game() : Core(), s()
		{
			setFood();
		}

		void update() override
		{
			Core::update();

			// set controls
			s.setDirection();

			// snake movement
			if(mTimer > s.speed)
			{
				s.move();
				mTimer = 0;
			}
			mTimer += delta;

			// check if snake eats food
			if(s.checkFood(food))
				setFood();

			// check if snake hits itself
			if(s.loseGame())
			{
				printf("game lost\n");
			}

			// render snake
			for(size_t i = 0; i < (size_t)s.blocks.size(); i++)
			{
				drawRectangle(s.blocks[i], blockSize, i == 0 ? s.secondColor : s.color);
			}

			// render food
			drawRectangle(food, blockSize, BLUE);

			if(screenResized)
				resize();
		}

		void setFood()
		{
			food = Vec2f(rnd<float>::randomValue(GetScreenWidth() - bsx, 0), rnd<float>::randomValue(GetScreenHeight() - bsy, 0));

			// food cannot spawn in snake
			for(auto& b : s.blocks)
				if(food.x + bsx > b.x && food.x < b.x + bsx && food.y < b.y + bsy && food.y + bsy > b.y)
					setFood();
		}

		void resize()
		{
			blockSize = Vec2f((float)GetScreenHeight() / 20, (float)GetScreenHeight() / 20);
		}

	private:
		Snake s;
		Vec2f food;
		double mTimer = 0;
		bool gameOver = false;
};

int main(int argc, char** argv)
{
	Game g;
	g.start();

	return 0;
}

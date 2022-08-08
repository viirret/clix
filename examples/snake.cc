#include "../clix/Core.hh"
#include "../clix/Controls.hh"

// blockSize depends on screen's value so it's defined after Core()
Vec2f blockSize;

class Snake
{
	public:
		void initialize()
		{
			for(size_t i = 0; i < (size_t)initialAmount; i++)
			{
				addBlock(Vec2f(i * blockSize.x + GetScreenWidth(), (float)GetScreenHeight()));
			}
		}

		void setDirection()
		{
			if(Controls::up()) direction = 1;
			if(Controls::down()) direction = 2;
			if(Controls::left()) direction = 3;
			if(Controls::right()) direction = 4;
		}

		void move()
		{
			Vec2f oldBlock = blocks[0];

			switch(direction)
			{
				case 1: blocks[0].y -= blockSize.y; break;
				case 2: blocks[0].y += blockSize.y; break;
				case 3: blocks[0].x -= blockSize.x; break;
				case 4: blocks[0].x += blockSize.x; break;
			}

			for(size_t i = 0; i < (size_t)blocks.size(); i++)
			{
				if(i != 0)
				{
					Vec2f newBlock = blocks[i];
					blocks[i] = oldBlock;
					oldBlock = newBlock;
				}
			}
		}

		void addBlock(Vec2f position)
		{
			blocks.push_back(position);
		}

		double speed = 2.0;
		int size = 3;
		Color color = RED;
		Color secondColor = BLACK;
		int initialAmount = 5;

		// the initial direction of the snake (1..4)
		int direction = 3;

		std::vector<Vec2f> blocks;
};

class Game : public Core
{
	public:
		Game() : Core()
		{
			resize();
			s.initialize();
		}

		void update() override
		{
			Core::update();

			s.setDirection();

			if(timer > s.speed)
			{
				s.move();
				timer = 0.0;
			}
			timer += delta;

			for(size_t i = 0; i < (size_t)s.blocks.size(); i++)
			{
				drawRectangle(s.blocks[i], blockSize, (i == 0) ? s.secondColor : s.color);
			}

			if(screenResized)
				resize();
		}

		void resize()
		{
			blockSize = Vec2f((float)GetScreenHeight() / 20, (float)GetScreenHeight() / 20);
		}
	private:
		Snake s;
		double timer;
};

int main(int argc, char** argv)
{
	Game g;
	g.start();

	return 0;
}

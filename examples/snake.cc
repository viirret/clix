#include "../clix/Core.hh"
#include "../clix/Controls.hh"

#define bsx blockSize.x
#define bsy blockSize.y

// blockSize depends on screen's value
Vec2f blockSize;
const double foodSpawnRate = 20;

class Food
{
	public:
		void createFood()
		{
			exists = true;
			coord = Vec2f(rnd<float>::randomValue(GetScreenWidth() - bsx, 0), rnd<float>::randomValue(GetScreenHeight() - bsy, 0));
		}

		bool exists;
		Vec2f coord;
		Color color = BLUE;
};

class Snake
{
	public:
		Snake()
		{
			for(size_t i = 0; i < (size_t)initialAmount; i++)
			{
				addBlock(Vec2f(i * bsx + GetScreenWidth(), (float)GetScreenHeight()));
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
				case 1: blocks[0].y -= bsy; break;
				case 2: blocks[0].y += bsy; break;
				case 3: blocks[0].x -= bsx; break;
				case 4: blocks[0].x += bsx; break;
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

		// check if snake hits the food from all directions
		bool checkFood(Food& f)
		{
			Vec2f hit = blocks[0];

			if(hit.x + bsx > f.coord.x && hit.x < f.coord.x + bsx && hit.y < f.coord.y + bsy && hit.y + bsy > f.coord.y)
			{
				addBlock(Vec2f(blocks.back().y + blockSize.y, blocks.back().x + blockSize.x));
				f.coord = Vec2f(-bsx, -bsy);
				return true;
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
		Game() : Core(), s(){}

		void update() override
		{
			Core::update();

			s.setDirection();

			if(s.checkFood(f))
			{
				f.exists = false;
			}

			if(!f.exists)
			{
				fTimer > foodSpawnRate ? f.createFood(), fTimer = 0 : fTimer += delta;
			}

			if(mTimer > s.speed)
			{
				s.move();
				mTimer = 0;
			}

			mTimer += delta;

			for(size_t i = 0; i < (size_t)s.blocks.size(); i++)
			{
				drawRectangle(s.blocks[i], blockSize, i == 0 ? s.secondColor : s.color);
			}

			drawRectangle(f.coord, blockSize, f.color);

			if(screenResized)
				resize();
		}

		void resize()
		{
			blockSize = Vec2f((float)GetScreenHeight() / 20, (float)GetScreenHeight() / 20);
		}

	private:
		Snake s;
		Food f;
		double mTimer = 0;
		double fTimer = 0;
		bool gameOver = false;
};

int main(int argc, char** argv)
{
	Game g;
	g.start();

	return 0;
}

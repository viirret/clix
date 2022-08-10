#include "../clix/Core.hh"
#include "../clix/Controls.hh"

#define bsx blockSize.x
#define bsy blockSize.y

// blockSize depends on screen's value
Vec2f blockSize;
const double foodSpawnRate = 0;

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

class Food
{
	public:
		void createFood(Snake& s)
		{
			coord = Vec2f(rnd<float>::randomValue(GetScreenWidth() - bsx, 0), rnd<float>::randomValue(GetScreenHeight() - bsy, 0));

			for(int i = 0; i < (int)s.blocks.size(); i++)
			{
				if(coord.x + bsx > s.blocks[i].x && coord.x < s.blocks[i].x + bsx && coord.y < s.blocks[i].y + bsy && coord.y + bsy > s.blocks[i].y)
				{
					createFood(s);
				}
			}

			exists = true;
		}

		bool exists;
		Vec2f coord;
		Color color = BLUE;
};


class Game : public Core
{
	public:
		Game() : Core(), s(){}

		void update() override
		{
			Core::update();

			s.setDirection();

			if(s.checkFood(f.coord))
			{
				f.exists = false;
			}

			if(!f.exists)
			{
				fTimer > foodSpawnRate ? f.createFood(s), fTimer = 0 : fTimer += delta;
			}

			if(mTimer > s.speed)
			{
				s.move();
				mTimer = 0;
			}

			mTimer += delta;

			if(s.loseGame())
			{
				printf("game lost\n");
			}

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

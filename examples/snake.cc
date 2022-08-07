#include "../clix/Core.hh"

Vec2f blockSize;

class Snake
{
	public:
		Snake()
		{
			for(int i = 0; i < 3; i++)
			{
				addBlock(Vec2f(i * blockSize.x, 0));
			}
		}

		void addBlock(Vec2f position)
		{
			blocks.push_back(position);
		}

		double speed = 2.0;
		int size = 3;
		Color color = RED;

		std::vector<Vec2f> blocks;
};

class Game : public Core
{
	public:
		Game() : Core()
		{
			resize();
		}

		void update() override
		{
			Core::update();

			for(auto& b : s.blocks)
			{
				drawRectangle(b, blockSize, s.color);
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
};

int main(int argc, char** argv)
{
	Game g;
	g.start();

	return 0;
}

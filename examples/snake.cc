#include "../clix/Core.hh"

Vec2f blockSize;

class Snake
{
	public:
		Snake()
		{
			for(int i = 0; i < 3; i++)
				addBlock();
		}

		void addBlock()
		{
			blocks.push_back(blockSize);
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

			// TODO check what is wrong with cursor
			EnableCursor();

			for(auto& b : s.blocks)
			{
				drawRectangle(Vec2f(50, 50), blockSize, s.color);
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

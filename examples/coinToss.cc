#include "../clix/Core.cc"
#include <cmath>

class Game : public Core
{
	public:
		Game() : heads("heads.png"), tails("tails.png")
		{
			isHeads = flip();
		}

		void update() override
		{
			Core::update();
			isHeads ? heads.draw() : tails.draw();
		}

		bool flip()
		{
			return std::round(rnd<float>::randomValue(0.f, 1.f)) == 1;
		}

		private:
			Img heads, tails;
			bool isHeads;
};

int main(int argc, char** argv)
{
	Game g;
	g.start();

	return 0;
}

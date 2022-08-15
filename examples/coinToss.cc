#include "../clix/Core.cc"
#include <cmath>

class Game : public Core
{
	public:
		Game()
		// initialize images
		{

		}
		void update() override
		{
			Core::update();
		}

		bool flip()
		{
			if(std::floor(rnd<float>::randomValue(0.f, 1.f)) == 1)
			{
				return true;
			}
			return false;
		}

	private:
		Img startButton, heads, tails;

};

int main(int argc, char** argv)
{
	Game g;
	g.start();

	return 0;
}

#include "Game.hh"

int main(int argc, char** argv)
{
	Game g;

	while(!g.close)
		g.update();

	return 0;
}

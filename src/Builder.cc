#include "Builder.hh"

Builder::Builder(): program(), game() {}

void Builder::update()
{
	if(program.close)
		this->close = true;
	else
	{
		program.run();
		game.update();
	}
}

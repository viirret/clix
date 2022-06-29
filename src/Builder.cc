#include "Builder.hh"

Builder::Builder(): program(), playGround() {}

void Builder::update()
{
	if(program.close)
		this->close = true;
	else
	{
		program.run();
		playGround.update();
	}
}

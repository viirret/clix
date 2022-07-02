#ifndef TICTACTOE_HH
#define TICTACTOE_HH

#include "../clix/Core.hh"

class tictactoe : public Core
{
	public:
		tictactoe();
		void update();
	
	private:
		void draw();

};

#endif

#include "Program.hh"

int main(int argc, char** argv)
{
	Program p;

	while(!p.close)
		p.run();

	return 0;
}

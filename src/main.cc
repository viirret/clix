#include "Builder.hh"

int main(int argc, char** argv)
{
	Builder b;

	while(!b.close)
		b.update();

	return 0;
}

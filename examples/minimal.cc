#include "../clix/Core.hh"

// minimal code required for creating empty white screen

class A : public Core
{
	public:
		A() : Core() {}
		
		void update() override
		{
			Core::update(); 
		}
};

int main(int argc, char** agrv)
{
	A a;
	a.start();

	return 0;
}

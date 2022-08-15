#include "../clix/Core.hh"

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

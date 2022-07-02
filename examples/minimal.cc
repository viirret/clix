#include "Core.hh"

class A : public Core
{
	public:
		A() : Core() {};
		
		void update() 
		{
			Core::update(); 
		}
};

int main(int argc, char** agrv)
{
	A a;

	while(!a.close)
		a.update();

	return 0;
}

# clix
Clix is object-oriented 2D framework for creating games.

The goal of this project is to be able to create simple 2D games with little code needed.

This project is not a wrapper library like [raylib-cpp](https://github.com/RobLoach/raylib-cpp), but a framework with bigger abstractions and more object-oriented style.

# Dependencies
Only dependency for this project is Raylib.

You can get Raylib from [https://www.raylib.com](https://www.raylib.com)

For Arch Linux
```
sudo pacman -S raylib
```
# How to use Clix
Start by cloning this repository
```
git clone https://github.com/viirret/clix.git
```
and enter it's directory
```
cd clix
```
In order to see if everything works try to run the [snake game](https://github.com/viirret/clix/blob/main/examples/snake.cc) that is included in this project.


Enter the commands
```
mkdir build && cd build
```
```
cmake ..
```
```
make
```
or run the script that does the same thing
```
chmod +x build.sh && ./build.sh
```

then you can run created binary **./x** found in **build**.

In order to create your own programs start by looking at [examples](https://github.com/viirret/clix/blob/main/examples/) and the [config file](https://github.com/viirret/clix/blob/main/clix/Config.cc).

The minimal code required to make window looks like
```cpp
#include "clix/Core.hh"

class A : public Core
{
    public:
        A() : Core() {}
		
        void update() override
        {
            Core::update();
        }
};

int main()
{
    A a;
    a.start();
	
    return 0;
}
```

When creating your own files remember to edit **CMakeLists.txt**



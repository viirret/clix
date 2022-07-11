#include "../clix/Core.hh"
#include "../clix/Crosshair.hh"
#include "../clix/Player.hh"

class Enemy : public Img
{
	public:
		Enemy(std::string path, Vec2f position) : Img(path, position)
		{
			type = Object::Type::enemy;
		}
};

class Ammo : public Img
{
	public:
		Ammo(std::string path, Vec2f position) : Img(path, position)
		{
			type = Object::Type::ammo;
		}
};

class clickerGame2 : public Core
{
	public:
		clickerGame2() 
				: Core(),
				  crosshair(),
				  player()
		{
			images.push_back(std::make_unique<Enemy>("arch.png", Vec2f(0, 0)));
		}

		void update() override
		{
			Core::update();
			crosshair.updateCrosshair(mousePosition);

			// render images
			for(auto& obj : images)
				obj->draw();

			if(IsMouseButtonPressed(0))
			{
				if(player.gun.getCapacity() > 0)
				{
					audio.playSound("gunshow.mp3");

					// update mag size
					player.gun.fire();
				}
			}

			crosshair.draw();
		}

	private:
		Crosshair crosshair;
		Player player;
};

int main(int argc, char** argv)
{
	clickerGame2 c;
	c.start();
	return 0;
}

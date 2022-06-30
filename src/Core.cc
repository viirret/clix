#include "Core.hh"

Core::Core() : audio()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "");
	HideCursor();
}

Core::~Core()
{
	CloseWindow();
}

void Core::update()
{
	events();
}

void Core::events()
{
	// default raylib closing
	if(WindowShouldClose())
		close = true;

	// always track mouse position
	mousePosition = Vec2f(GetMousePosition().x, GetMousePosition().y);

	// get vector2 on mouse position when clicked
	if(IsMouseButtonPressed(0))
	{
		currentClick = mousePosition;
	}

		/*
		if(player.gun.getCapacity() > 0)
		{
			audio.playSound("gunshow.mp3");

			// update mag size
			player.gun.fire();
		}
		*/
}

void Core::spawnEnemyRandom(std::string texture)
{
	auto obj = std::make_unique<Object>((glb::assetsPath + texture).c_str());
	
	// we need textures size for random position
	obj->setPosition(getRandomSpawn(obj->getTexture()));
	obj->setType(Object::Type::enemy);
	objects.push_back(std::move(obj));
}

const Vec2f Core::getRandomSpawn(Texture texture)
{
	float a = rnd<float>::randomValue(0.0f, (float)GetScreenWidth() - texture.width);
	float b = rnd<float>::randomValue(0.0f, (float)GetScreenHeight() - texture.height);
	return Vec2f(a, b);
}


#include "Core.hh"

Core::Core() : audio()
{
	SetConfigFlags(Config::CONFIGFLAGS);
	
	InitWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, "");

	if(Config::HIDECURSOR)
		HideCursor();
}

Core::Core(std::string name) : audio()
{
	SetConfigFlags(Config::CONFIGFLAGS);
	
	InitWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, name.c_str());

	if(Config::HIDECURSOR)
		HideCursor();
}

Core::~Core()
{
	CloseWindow();
}

void Core::update()
{
	events();
	raylibDrawing();
}

void Core::start()
{
	while(!close)
		update();
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
		currentClick = mousePosition;

	if(IsMouseButtonReleased(0))
		currentClick = Vec2f(-1, -1);

	if(IsWindowResized() && !IsWindowFullscreen())
	{
		Config::WINDOW_WIDTH = GetScreenWidth();
		Config::WINDOW_WIDTH = GetScreenHeight();
		screenResized = true;
	}
	else
		screenResized = false;
}

void Core::raylibDrawing()
{
	ClearBackground(Config::BACKGROUND);
	BeginDrawing();
	EndDrawing();
}

void Core::spawnEnemyRandom(std::string texture)
{
	auto obj = std::make_unique<Img>((Config::ASSETSPATH + texture).c_str());
	
	// we need textures size for random position
	obj->setPosition(getRandomSpawn(obj->getTexture()));
	obj->setId("enemy");
	images.push_back(std::move(obj));
}

const Vec2f Core::getRandomSpawn(Texture texture)
{
	float a = rnd<float>::randomValue(0.0f, (float)GetScreenWidth() - texture.width);
	float b = rnd<float>::randomValue(0.0f, (float)GetScreenHeight() - texture.height);
	return Vec2f(a, b);
}

void Core::drawRectangle(Vec2f position, Vec2f size, Color color)
{
	DrawRectangleV((Vector2){position.x, position.y}, (Vector2){size.x, size.y}, color);	
}

bool Core::isClicked(Vec2f position, Vec2f max)
{
	return currentClick.x >= position.x && currentClick.y >= position.y && currentClick.x && currentClick.x <= max.x && currentClick.y <= max.y;
}

bool Core::isClickedSize(Vec2f position, Vec2f size)
{
	return currentClick.x >= position.x && currentClick.y >= position.y && currentClick.x && currentClick.x <= position.x + size.x && currentClick.y <= position.y + size.y;
}



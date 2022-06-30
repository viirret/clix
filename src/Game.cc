#include "Game.hh"

Game::Game() 
	: 	Core(),		// start core
		crosshair() // implement default crosshair
{
	spawnEnemyRandom("arch.png");
}

void Game::update()
{
	Core::update();
	updateCrosshair();
	gameLogic();
	draw();
}

void Game::gameLogic()
{

}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	crosshair.draw(WHITE);

	// render enemies
	for(auto& obj : objects)
		obj->draw(WHITE);

	EndDrawing();
}

void Game::updateCrosshair()
{
	crosshair.updateCrosshair(getMousePosition());
}


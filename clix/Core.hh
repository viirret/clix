#ifndef CORE_HH
#define CORE_HH

#include "raylib.h"
#include "Vector2.hh"
#include "Crosshair.hh"
#include "Object.hh"
#include "Global.hh"
#include "Enemy.hh"
#include "Settings.hh"
#include "Audio.hh"
#include <memory>
#include <cstdio>
#include <vector>
#include <string>

class Core
{
	public:
		Core();
		virtual ~Core();
		void start();
	protected:
		// main update function for this framework
		virtual void update();

		// close program
		bool close = false;
		// last clicked position
		Vec2f currentClick;
		// current mouse position
		Vec2f mousePosition;

		// helper functions
		const Vec2f getRandomSpawn(Texture texture);
		void spawnEnemyRandom(std::string texture);

		bool isClicked(Vec2f position, Vec2f max);
		bool isClickedSize(Vec2f position, Vec2f size);

		// currently existing enemies
		std::vector<std::unique_ptr<Object>> objects;

		// drawing functions
		void drawRectangle(Vec2f position, Vec2f size, Color color);
		Audio audio;

	private:
		// functions running in main loop
		void events();
		void raylibDrawing();
};

#endif

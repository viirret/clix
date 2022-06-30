#ifndef CORE_HH
#define CORE_HH

#include "raylib.h"
#include "Vector2.hh"
#include "Crosshair.hh"
#include "Object.hh"
#include "Global.hh"
#include "Enemy.hh"
#include "Settings.hh"
#include <memory>
#include <cstdio>
#include <vector>
#include <string>

class Core
{
	public:
		Core();
		virtual ~Core();
		void update();
		bool close = false;
	protected:
		const Vec2f getMousePosition();
		const Vec2f getCurrentClickPosition();
		Vec2f getRandomSpawn(Texture texture);
		void spawnEnemyRandom(std::string texture);

		// currently existing enemies
		std::vector<std::unique_ptr<Object>> objects;

	private:
		// functions running in main loop
		void events();

		Vec2f currentClick;
		Vec2f mousePosition;

};

#endif

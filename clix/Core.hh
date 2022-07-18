#ifndef CORE_HH
#define CORE_HH

#include "raylib.h"
#include "Vector2.hh"
#include "Crosshair.hh"
#include "Object.hh"
#include "Global.hh"
#include "Audio.hh"
#include "Image.hh"
#include <memory>
#include <utility>
#include <cstdio>
#include <vector>
#include <string>

class Core
{
	public:
		Core();
		Core(std::string name);
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

		// currently existing objects
		std::vector<std::unique_ptr<Object>> objects;

		// currently existing images
		std::vector<std::unique_ptr<Img>> images;

		// drawing functions
		void drawRectangle(Vec2f position, Vec2f size, Color color);
		Audio audio;

		bool screenResized = false;

	private:
		// functions running in main loop
		void events();
		void raylibDrawing();
};

#endif

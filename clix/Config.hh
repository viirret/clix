#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include "raylib.h"

class Config
{
	public:
		// window size
		static int WINDOW_WIDTH;
		static int WINDOW_HEIGHT;

		// volume
		static int MASTER_VOLUME;

		// default path for assets
		static std::string ASSETSPATH;

		// hiding cursor
		static bool HIDECURSOR;
		
		// default background color
		static Color BACKGROUND;

		static int CONFIGFLAGS;
};

#endif

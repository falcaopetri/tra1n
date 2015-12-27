/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef CONFIG_H
#define CONFIG_H

#include "List.hpp"

#include <string>
#include <map>

namespace rails {
	class Config{
	public:
        static const char* windowTitle;

        static const int PositionIncrement;
        static std::map<std::string, char*> systemPaths;

        static const float FPS;

		static const int SCREEN_WIDTH;
		static const int SCREEN_HEIGHT;

		enum Screen {
			HOME, PLAY, ABOUT, PLAY_OFF, PLAY_END, HOWTO
		};

	};
}
#endif

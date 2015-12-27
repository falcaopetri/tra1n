/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <iostream>
#include <map>

#include <stdio.h>
#include <allegro5/allegro.h>

#include <allegro5/allegro_image.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdexcept>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Drawing.h"
#include "Config.h"
#include "Game.h"

namespace rails {
    class Screen;

    class IContext
    {
        public:
            IContext() {}
            virtual ~IContext() {}

            virtual void switchSound() = 0;
            virtual std::string getOppositeImage(std::string name) = 0;
            virtual rails::IDrawing* requestImage(std::string name) = 0;

            virtual void playSound(RailsUtil::Sound sound) = 0;

            virtual ALLEGRO_FONT* getFont() {
                return _font;
            }

            Game& getGame() {
                return _game;
            }

            virtual void changeToScreen(Config::Screen screenID) = 0;
        protected:
            virtual void setSound(RailsUtil::Sound sound) = 0;

            std::map<int, rails::Screen*> screens;
            Game _game;

            ALLEGRO_FONT* _font = nullptr;

            virtual rails::Screen* getScreen(Config::Screen screenID) = 0;
    };
}
#endif // ICONTEXT_H

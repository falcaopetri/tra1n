/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef RAILSGUI_H
#define RAILSGUI_H

#include "IContext.h"
#include "Screen.h"
#include "PlayScreen.h"
#include "RailsUtil.hpp"

namespace rails
{
    class RailsGUI : public IContext
    {
    public:
        RailsGUI();
        ~RailsGUI();

        void initAllegro();
        void loop();
        void shutdown();

        //virtual void startPlaying();

        int exitCode();
        virtual void playSound(RailsUtil::Sound sound);
        virtual void switchSound();
        virtual std::string getOppositeImage(std::string name);
        virtual rails::IDrawing* requestImage(std::string name);

    protected:
    private:
        virtual void setSound(RailsUtil::Sound sound);

        int _exitCode;

        ALLEGRO_DISPLAY* _display = nullptr;
        ALLEGRO_EVENT_QUEUE* _eventQueue = nullptr;
        ALLEGRO_TIMER* _timerDrawing = nullptr;
        ALLEGRO_TIMER* _timerPlaying = nullptr;
        ALLEGRO_TIMER* _timerAnimation = nullptr;
        ALLEGRO_SAMPLE_ID _musicId;

        RailsUtil::Sound _currentSound;
        Screen* _currentScreen = nullptr;

        std::map<std::string, IDrawing*> systemImages;
        std::map<int, ALLEGRO_SAMPLE*> sounds;

        bool soundOn = false;
        bool isPlayingSound = false;
        bool showQuestionImage = false;
        bool gameAnswer = true;
        bool redraw = true;
        bool doexit = false;
        bool abortGameFlag = false;
        int animate = 1;
        int alfa = 0;

        int status = 0;

        Screen* getScreen(Config::Screen screenID);
        void changeToScreen(Config::Screen screenID);

        void raiseError(std::string message, RailsUtil::ErrorType type);

        void addImageToScreen(std::string name, Config::Screen screen, bool visible);
        void removeImageFromScreen(std::string name, Config::Screen screen);
        bool loadSystemImage (std::string name, int xPos, int yPos, int actions, bool isactive, std::string bitmapName = "");

        void addPiece();
        void resetPositions();
    };
}
#endif // RAILSGUI_H

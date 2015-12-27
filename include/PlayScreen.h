/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include <Screen.h>
#include "ComposedDrawing.h"

namespace rails
{
    class PlayScreen : public Screen
    {
    public:
        PlayScreen(IContext* context);
        //virtual ~PlayScreen();

        bool checkEvents(ALLEGRO_EVENT& ev) override;

        bool isAnimating();

        virtual void draw() override;

        virtual void recalculate() override;
        virtual void reset() override;
    protected:
        bool drawingEvent(std::pair<std::string, IDrawing*> drawing, rails::RailsUtil::EventType event) override;
    private:
        bool canMove(IDrawing* d);

        bool _moving;

        int _stackCounter;

        RailsUtil::Animation _animation;
        RailsUtil::Position _position;
        RailsUtil::Pos _pos;
    };
}
#endif // PLAYSCREEN_H

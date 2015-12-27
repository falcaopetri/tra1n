/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef SCREEN_H
#define SCREEN_H

#include <map>
#include <iostream>
#include <typeinfo>
#include <string>
#include <allegro5/allegro.h>

#include "Drawing.h"
#include "ComposedDrawing.h"
#include "RailsUtil.hpp"
#include "IContext.h"

namespace rails
{
    class Screen
    {
    public:
        Screen(IContext* context);
        //virtual ~Screen();

        virtual void draw();

        virtual bool checkEvents(ALLEGRO_EVENT& ev);

        void addDrawing(std::string name, IDrawing* drawing, bool visible);
        void removeDrawing(std::string name);
        IDrawing* getDrawing(std::string name);

        virtual void recalculate();
        virtual void reset();
    protected:
        std::map<std::string, IDrawing*> _drawings;
        IContext* _context;

        void requestOpposite(std::string name);

        void draw(Drawing* drawing, bool mustBeActive);
        void draw(ComposedDrawing* drawing);
        virtual bool drawingEvent(std::pair<std::string, IDrawing*> drawing, rails::RailsUtil::EventType event);
    };
}
#endif // SCREEN_H

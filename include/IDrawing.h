/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef IDRAWING_H
#define IDRAWING_H

#include <iostream>
#include "Point.h"
namespace rails {
    class IDrawing
    {
        public:
            IDrawing(Point point, unsigned actions, bool isactive);

            /*
                Setta _hasFocus para true caso a posição @param (mouse_x, mouse_y)
                esteja em cima da imagem
            */
            virtual void checkOver(Point p) = 0;

            virtual bool checkCollision(rails::IDrawing* d) = 0;

            virtual unsigned getActions() = 0;

            virtual int getWidth() = 0;
            virtual int getHeight() = 0;

            rails::Point getPoint();

            virtual void destroy() = 0;

            bool hasFocus();
            bool isActive();
            void setActive(bool isactive);

            virtual void move(Point p) = 0;
            virtual void moveTo(Point p) = 0;

            void addActions(unsigned int acts);
            void removeActions(unsigned int acts);
         protected:
         	rails::Point _point;

         	bool _hasFocus = false;
         	bool _isActive = false;

         	unsigned _actions = 0;
    };
}
#endif // DRAWING_H

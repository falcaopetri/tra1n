/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef DRAWING_H
#define DRAWING_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <iostream>

#include "IDrawing.h"

namespace rails {
    class Drawing : public IDrawing
    {
        public:
            Drawing(Point point, ALLEGRO_BITMAP* bitmap, unsigned actions, bool isactive);
            //virtual ~Drawing();

            ALLEGRO_BITMAP* getBitmap();

            virtual void destroy() override;
            /*
                Setta _hasFocus para true caso a posição @param (mouse_x, mouse_y)
                esteja em cima da imagem
            */
            virtual void checkOver(Point p) override;

            virtual bool checkCollision(IDrawing* d) override;

            virtual unsigned getActions() override;

            virtual void move(Point p) override;
            virtual void moveTo(Point p) override;

            virtual int getWidth() override;
            virtual int getHeight() override;
        private:
            ALLEGRO_BITMAP* _bitmap;
    };
}
#endif // DRAWING_H

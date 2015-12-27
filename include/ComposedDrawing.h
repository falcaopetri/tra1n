/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef COMPOSED_DRAWING_H
#define COMPOSED_DRAWING_H

#include <algorithm>

#include "IDrawing.h"
namespace rails {
    class ComposedDrawing : public IDrawing
    {
    public:
        ComposedDrawing();

        void setDrawings(IDrawing* drawing1, IDrawing* drawing2);

        virtual void checkOver(Point p) override;
        virtual bool checkCollision(rails::IDrawing* d) override;
        virtual unsigned getActions() override;
        virtual int getWidth();
        virtual int getHeight();

        virtual void destroy() override;

        virtual void move(Point p) override;
        virtual void moveTo(Point p) override;

        IDrawing* getDrawing1();
        IDrawing* getDrawing2();
    private:
        IDrawing* _drawing1;
        IDrawing* _drawing2;
    };
}

#endif // COMPOSED_DRAWING_H

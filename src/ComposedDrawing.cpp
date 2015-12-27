/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "ComposedDrawing.h"

rails::ComposedDrawing::ComposedDrawing()
    : IDrawing(Point(0,0), 0, false)
{
    _drawing1 = _drawing2 = nullptr;
}

void rails::ComposedDrawing::setDrawings(IDrawing* drawing1, IDrawing* drawing2) {
    _drawing1 = drawing1;
    if (_drawing1) {
        _point = _drawing1->getPoint();
    }

    _drawing2 = drawing2;
    if (_drawing2) {
        _point = Point(std::min(_point.X, _drawing2->getPoint().X),
                       std::min(_point.Y, _drawing2->getPoint().Y));
    }
}

void rails::ComposedDrawing::checkOver(Point p) {
    if (_drawing1)
        _drawing1->checkOver(p);
    if (_drawing2)
        _drawing2->checkOver(p);
}

bool rails::ComposedDrawing::checkCollision(rails::IDrawing* d) {
    bool result = false;

    if (_drawing1 == d || _drawing2 == d)
        return false;

    if (_drawing1)
        result = _drawing1->checkCollision(d);

    if (_drawing2)
        result |= _drawing2->checkCollision(d);

    return result;
}

unsigned rails::ComposedDrawing::getActions() {
    unsigned result = 0;
    if (_drawing1)
        result = _drawing1->getActions();

    if (_drawing2)
        result |= _drawing2->getActions();

    return result;
}

rails::IDrawing* rails::ComposedDrawing::getDrawing1() {
    return _drawing1;
}
rails::IDrawing* rails::ComposedDrawing::getDrawing2() {
    return _drawing2;
}

void rails::ComposedDrawing::destroy() {
    if (_drawing1)
        _drawing1->destroy();
    if (_drawing2)
        _drawing2->destroy();
}
void rails::ComposedDrawing::move(Point p) {
    _point += p;
    if (_drawing1)
        _drawing1->move(p);
    if (_drawing2)
        _drawing2->move(p);
}
void rails::ComposedDrawing::moveTo(Point p) {
    _point = p;
}
int rails::ComposedDrawing::getWidth() {
    int width = 0;

    if (_drawing1)
        width = _drawing1->getWidth();

    if (_drawing2)
        width = std::max(width, _drawing2->getWidth());

    return width;
}
int rails::ComposedDrawing::getHeight() {
    int height = 0;

    if (_drawing1)
        height = _drawing1->getHeight();

    if (_drawing2)
        height = std::max(height, _drawing2->getHeight());

    return height;
}

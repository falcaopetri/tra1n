/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "IDrawing.h"

rails::IDrawing::IDrawing(Point p, unsigned actions, bool isactive)
    : _point(p), _actions(actions), _isActive(isactive)
{
    _hasFocus = false;
}

rails::Point rails::IDrawing::getPoint()
{
    return _point;
}

bool rails::IDrawing::hasFocus() {
    return _hasFocus;
}
void rails::IDrawing::addActions(unsigned int acts) {
    _actions |= acts;
}
void rails::IDrawing::removeActions(unsigned int acts) {
    _actions = _actions & ~acts;
}

bool rails::IDrawing::isActive() {
    return _isActive;
}

void rails::IDrawing::setActive(bool isactive) {
    _isActive = isactive;
}

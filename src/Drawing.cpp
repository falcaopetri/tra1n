/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Drawing.h"
rails::Drawing::Drawing(Point point, ALLEGRO_BITMAP* bitmap, unsigned actions, bool isactive = true)
    : IDrawing(point, actions, isactive)
{
    _bitmap = bitmap;
}

bool rails::Drawing::checkCollision(IDrawing* d) {
    // Reference:
    // https://wiki.allegro.cc/index.php?title=Collision_detection

    Point p = d->getPoint();

    return !((getPoint().X > p.X + d->getWidth() - 1) || // is b1 on the right side of b2?
        (getPoint().Y > p.Y + d->getHeight() - 1) || // is b1 under b2?
        (p.X > getPoint().X + getWidth() - 1) || // is b2 on the right side of b1?
        (p.Y > getPoint().Y + getHeight() - 1));   // is b2 under b1?

}
int rails::Drawing::getWidth()
{
    return al_get_bitmap_width(_bitmap);
}

void rails::Drawing::destroy() {
    if (_bitmap) al_destroy_bitmap(_bitmap);
    _bitmap = nullptr;
}
int rails::Drawing::getHeight()
{
    return al_get_bitmap_height(_bitmap);
}

unsigned rails::Drawing::getActions()
{
    return _actions;
}

void rails::Drawing::move(Point p) {
    _point += p;
}
void rails::Drawing::moveTo(Point p) {
    _point = p;
}
void rails::Drawing::checkOver(Point p)
{
    if(getPoint().X <= p.X && p.X <= getPoint().X + getWidth() &&
            getPoint().Y <= p.Y && p.Y <= getPoint().Y + getHeight())
    {
        _hasFocus = true;
    }
    else
    {
        _hasFocus = false;
    }
}

ALLEGRO_BITMAP* rails::Drawing::getBitmap()
{
    return _bitmap;
}


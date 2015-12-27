/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Image.h"

rails::Image::Image()
{ }

rails::Image::Image(int x, int y, ALLEGRO_BITMAP* bitmap)
    : _x(x), _y(y)
{
    _hasFocus = false;
    _bitmap = bitmap;
    _width = al_get_bitmap_width(bitmap);
    _height = al_get_bitmap_height(bitmap);
}

void rails::Image::checkOver(int x, int y)
{
    if(_x <= x && x <= _x + _width &&
            _y <= y && y <= _y + _height)
    {
        _hasFocus = true;
    }
    else
    {
        _hasFocus = false;
    }
}

int rails::Image::getX()
{
    return _x;
}

int rails::Image::getY()
{
    return _y;
}

ALLEGRO_BITMAP* rails::Image::getBitmap()
{
    return _bitmap;
}

bool rails::Image::hasFocus()
{
    return _hasFocus;
}

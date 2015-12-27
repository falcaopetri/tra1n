/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Screen.h"

rails::Screen::Screen(IContext* context)
    : _context(context)
{
}

void rails::Screen::addDrawing(std::string name, IDrawing* drawing, bool visible = true)
{
    if (_drawings.find(name) == _drawings.end())
        _drawings[name] = drawing;

    _drawings[name]->setActive(visible);
}
void rails::Screen::removeDrawing(std::string name)
{
    //_drawings.erase(name);
    if (_drawings.find(name) != _drawings.end())
        _drawings[name]->setActive(false);
}
void rails::Screen::requestOpposite(std::string name)
{
    std::string opposite = _context->getOppositeImage(name);
    addDrawing(opposite, _context->requestImage(opposite),true);
    _drawings[name]->setActive(false);
}
bool rails::Screen::drawingEvent(std::pair<std::string, IDrawing*> drawing, rails::RailsUtil::EventType event)
{
    if (drawing.second->isActive())
    {
        unsigned flag = drawing.second->getActions();
        if (drawing.second->hasFocus())
        {
            if (event == rails::RailsUtil::EventType::LEFT_CLICK)
            {
                if (RailsUtil::isFlagSet(flag, RailsUtil::Action::SOUND))
                {
                    _context->switchSound();

                    requestOpposite(drawing.first);
                    return true;
                }
                else if (RailsUtil::isFlagSet(flag, RailsUtil::Action::GOTO_PLAY))
                {
                    _context->changeToScreen(Config::Screen::PLAY);
                }
                else if (RailsUtil::isFlagSet(flag, RailsUtil::Action::GOTO_HOME))
                {
                    if (!_context->getGame().hasFinished())
                        _context->getGame().finishGame();

                    _context->changeToScreen(Config::Screen::HOME);
                }
                else if (RailsUtil::isFlagSet(flag, RailsUtil::Action::GOTO_ABOUT))
                {
                    _context->changeToScreen(Config::Screen::ABOUT);
                }
                else if (RailsUtil::isFlagSet(flag, RailsUtil::Action::GOTO_HOWTO))
                {
                    _context->changeToScreen(Config::Screen::HOWTO);
                }
                else if (RailsUtil::isFlagSet(flag, RailsUtil::Action::HOWTO_NEXT))
                {
                    _drawings["howPlayFull"]->move(Point(-1200, 0));
                    _drawings["left"]->setActive(true);
                    if (_drawings["howPlayFull"]->getPoint().X == 4 * -1200)
                    {
                        _drawings["right"]->setActive(false);
                    }
                    else
                    {
                        _drawings["right"]->setActive(true);
                    }

                    int active = _drawings["howPlayFull"]->getPoint().X / -1200;
                    std::string imageON = "sliderNode" + std::to_string(active) + "F";
                    std::string imageOFF = "sliderNode" + std::to_string(active-1) + "N";

                    requestOpposite(imageON);
                    requestOpposite(imageOFF);
                }
                else if (RailsUtil::isFlagSet(flag, RailsUtil::Action::HOWTO_PREV))
                {
                    _drawings["howPlayFull"]->move(Point(1200, 0));
                    _drawings["right"]->setActive(true);
                    if (_drawings["howPlayFull"]->getPoint().X == 0)
                    {
                        _drawings["left"]->setActive(false);
                    }
                    else
                    {
                        _drawings["left"]->setActive(true);
                    }

                    int active = _drawings["howPlayFull"]->getPoint().X / -1200;
                    std::string imageON = "sliderNode" + std::to_string(active+1) + "N";
                    std::string imageOFF = "sliderNode" + std::to_string(active) + "F";

                    requestOpposite(imageON);
                    requestOpposite(imageOFF);
                }
            }

            else if (event == rails::RailsUtil::EventType::MOUSE_MOVE && RailsUtil::isFlagSet(flag, RailsUtil::Action::MOUSE_OVER))
            {
                requestOpposite(drawing.first);
                return true;
            }
        }
        else
        {
            if (event == rails::RailsUtil::EventType::MOUSE_MOVE && RailsUtil::isFlagSet(flag, RailsUtil::Action::MOUSE_EXIT))
            {
                requestOpposite(drawing.first);
                return true;
            }
        }
    }

    return false;
}

void rails::Screen::recalculate()
{

}
void rails::Screen::reset()
{
    for (auto &drawing : _drawings)
    {
        // TODO
        // request opposite image
        if (drawing.second && drawing.second->hasFocus())
        {
            if (RailsUtil::isFlagSet(drawing.second->getActions(), RailsUtil::Action::MOUSE_EXIT))
            {
                requestOpposite(drawing.first);

                drawing.second->checkOver(Point(-100, -100));
            }
        }
        std::string imageName = "sliderNode";

        if (_drawings.find(imageName+"0N") != _drawings.end())
        {
            for (int i = 0; i < 5; ++i)
            {
                std::string imageNameN = imageName + std::to_string(i) + "N";
                if (_drawings[imageNameN]->isActive())
                    requestOpposite(imageNameN);
            }
            _drawings[imageName+"0N"]->setActive(true);
            _drawings[imageName+"0F"]->setActive(false);


            _drawings["left"]->setActive(false);
            _drawings["right"]->setActive(true);

            _drawings["howPlayFull"]->moveTo(Point(0,0));

        }
    }
}
rails::IDrawing* rails::Screen::getDrawing(std::string name)
{
    return _drawings[name];
}

bool rails::Screen::checkEvents(ALLEGRO_EVENT& ev)
{
    if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)   //check if the mouse moved
    {
        for (auto &drawing : _drawings)
        {
            drawing.second->checkOver(Point(ev.mouse.x, ev.mouse.y));
            if (drawingEvent(drawing, rails::RailsUtil::MOUSE_MOVE)) return true;
        }
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        for (auto &drawing : _drawings)
        {
            if (drawingEvent(drawing, rails::RailsUtil::LEFT_CLICK)) return true;
        }
    }
    return false;
}
/*
    Desenha uma Image na tela de acordo com o identificador @name
*/
void rails::Screen::draw(Drawing* drawing, bool mustBeActive = true)
{

    if (drawing->isActive() || !mustBeActive)
    {
        ALLEGRO_BITMAP* bitmap = drawing->getBitmap();
        if (bitmap)
            al_draw_bitmap(bitmap,
                           drawing->getPoint().X, drawing->getPoint().Y, 0);
    }
}

void rails::Screen::draw(ComposedDrawing* drawing)
{
    if (drawing->isActive())
    {
        IDrawing* d1 = drawing->getDrawing1();
        IDrawing* d2 = drawing->getDrawing2();

        if (d1)
        {
            if (Drawing* derived = dynamic_cast<Drawing*>(d1))
            {
                draw(derived, false);
            }
            else if (ComposedDrawing* derived = dynamic_cast<ComposedDrawing*>(d1))
            {
                draw(derived);
            }
        }
        if (d2)
        {
            if (Drawing* derived = dynamic_cast<Drawing*>(d2))
            {
                draw(derived, false);
            }
            else if (ComposedDrawing* derived = dynamic_cast<ComposedDrawing*>(d2))
            {
                draw(derived);
            }
        }
    }
}

void rails::Screen::draw()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    for (auto &drawing : _drawings)
    {
        if (typeid(*(drawing.second)) == typeid(Drawing))
        {
            draw((Drawing*)drawing.second);
        }
        else if (typeid(*(drawing.second)) == typeid(ComposedDrawing))
        {
            draw((ComposedDrawing*)drawing.second);
        }
    }
}

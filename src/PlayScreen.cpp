/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "PlayScreen.h"

rails::PlayScreen::PlayScreen(IContext* context)
    : rails::Screen::Screen(context)
{
    _moving = false;
    _animation = RailsUtil::Animation::NONE;
    _position = RailsUtil::Position::QUEUE;
    _pos = RailsUtil::Pos::UP;
    _stackCounter = 0;
}

bool rails::PlayScreen::isAnimating()
{
    return _animation != RailsUtil::Animation::NONE;
}

void rails::PlayScreen::reset()
{
    Screen::reset();

    _stackCounter = 0;

    _drawings["correctAnswer"]->setActive(false);
    _drawings["cincorrectAnswer"]->setActive(false);

    _moving = false;
    _animation = RailsUtil::Animation::NONE;
    _position = RailsUtil::Position::QUEUE;
    _pos = RailsUtil::Pos::UP;

    ComposedDrawing* comp = (ComposedDrawing*) _drawings["craneComposing"];
    comp->setDrawings(_drawings["craneGreenComp"], nullptr);
    comp->setActive(true);

    requestOpposite("light1N");
    requestOpposite("light2N");
}
bool rails::PlayScreen::checkEvents(ALLEGRO_EVENT& ev)
{
    if (Screen::checkEvents(ev))
    {
        return true;
    }
    if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        switch(ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_A:
            if (!isAnimating() && !_context->getGame().hasFinished())
            {
                if (_pos == RailsUtil::Pos::UP || _position != RailsUtil::Position::QUEUE)
                {
                    if (_context->getGame().queueToCurrent())
                    {
                        requestOpposite("light1F");
                        _animation = RailsUtil::Animation::MOVE_WAGONS;
                    }
                }
            }
            return true;
            break;
        case ALLEGRO_KEY_D:
            if (!isAnimating() && !_context->getGame().hasFinished())
            {
                if (_pos == RailsUtil::Pos::UP || _position != RailsUtil::Position::QUEUE)
                {
                    ComposedDrawing* comp = (ComposedDrawing*) _drawings["craneComposing"];
                    if (_context->getGame().hasCurrentPiece()
                            && comp->getDrawing2() == nullptr)
                    {
                        requestOpposite("light2F");

                        _animation = RailsUtil::Animation::GO_TO_OUTPUT;
                    }
                }
            }
            return true;
            break;
        case ALLEGRO_KEY_LEFT:
            if (!isAnimating())
            {
                if (_pos == RailsUtil::Pos::UP)
                {
                    if (_position == RailsUtil::Position::QUEUE)
                    {
                        _animation = RailsUtil::Animation::GO_TO_STACK;
                        _position = RailsUtil::Position::STACK;
                    }
                }
                else if (_position == RailsUtil::Position::OUTPUT)
                {
                    _animation = RailsUtil::Animation::GO_TO_QUEUE;
                    _position = RailsUtil::Position::QUEUE;
                }
            }

            return true;
            break;
        case ALLEGRO_KEY_RIGHT:
            if (!isAnimating())
            {
                if (_pos == RailsUtil::Pos::UP)
                {
                    if (_position == RailsUtil::Position::STACK)
                    {
                        _animation = RailsUtil::Animation::GO_TO_QUEUE;
                        _position = RailsUtil::Position::QUEUE;
                    }
                }
            }
            return true;
            break;
        case ALLEGRO_KEY_UP:
            if (!isAnimating())
            {
                _animation = RailsUtil::Animation::GO_UP;
                _pos = RailsUtil::Pos::UP;
                _context->playSound(RailsUtil::Sound::UPS);
            }
            return true;
            break;
        case ALLEGRO_KEY_DOWN:
            if (!isAnimating())
            {
                _animation = RailsUtil::Animation::GO_DOWN;
                _pos = RailsUtil::Pos::DOWN;
                _context->playSound(RailsUtil::Sound::DOWNS);

            }
            return true;
            break;
        }
    }

    return false;
}
void rails::PlayScreen::draw()
{
    Screen::draw();

    char timing[10];
    int time = _context->getGame().getScore().getTiming();
    sprintf(timing, "%2d", time);

    al_draw_text(_context->getFont(), al_map_rgb(255,0,0),
                 100, 100, ALLEGRO_ALIGN_CENTRE, timing);

    if (_context->getGame().hasFinished())
    {
        _context->playSound(RailsUtil::Sound::TRAIN);
        if (_context->getGame().isCorrect())
        {
            // correct
            _drawings["correctAnswer"]->setActive(true);
        }
        else
        {
            // not correct
            _drawings["cincorrectAnswer"]->setActive(true);
        }
    }
}
void rails::PlayScreen::recalculate()
{
    switch (_animation)
    {
    case RailsUtil::Animation::GO_UP:
        if (_drawings["craneComposing"]->getPoint().Y > -279)
            _drawings["craneComposing"]->move(Point(0, -Config::PositionIncrement));
        else
            _animation = RailsUtil::Animation::NONE;
        break;
    case RailsUtil::Animation::GO_DOWN:
        if (_position == RailsUtil::Position::QUEUE)
        {
            if (_drawings["craneComposing"]->getPoint().Y < -10)
            {
                _drawings["craneComposing"]->move(Point(0, Config::PositionIncrement));
            }
            else
            {
                ComposedDrawing* comp = (ComposedDrawing*) _drawings["craneComposing"];
                if (_context->getGame().hasCurrentPiece())
                {
                    _drawings["craneGreenComp"]->moveTo(comp->getPoint());
                    _drawings["craneRedComp"]->moveTo(comp->getPoint());

                    std::string name = _context->getGame().getCurrentPiece().getId();
                    if (RailsUtil::isFlagSet(_drawings[name]->getActions(), RailsUtil::Action::ATTACH))
                    {
                        _drawings[name]->addActions(RailsUtil::Action::CAN_MOVE);
                        _drawings[name]->removeActions(RailsUtil::Action::ATTACH);

                        comp->setDrawings(_drawings["craneRedComp"], _drawings[name]);
                    }
                    else
                    {
                        _drawings[name]->removeActions(RailsUtil::Action::CAN_MOVE);
                        _drawings[name]->addActions(RailsUtil::Action::ATTACH);
                        comp->setDrawings(_drawings["craneGreenComp"], nullptr);
                    }
                    comp->setActive(true);


                }
                _animation = RailsUtil::Animation::NONE;
            }
        }
        else if (_position == RailsUtil::Position::STACK)
        {
            ComposedDrawing* comp = (ComposedDrawing*) _drawings["craneComposing"];
            if (comp->getDrawing2() == nullptr && _drawings["craneComposing"]->getPoint().Y < -145 - (_stackCounter-1) * 30)
            {
                _drawings["craneComposing"]->move(Point(0, Config::PositionIncrement));
            }
            else if (comp->getDrawing2() != nullptr && _drawings["craneComposing"]->getPoint().Y < -145 - _stackCounter * 30)
            {
                _drawings["craneComposing"]->move(Point(0, Config::PositionIncrement));
            }
            else
            {
                _drawings["craneGreenComp"]->moveTo(comp->getPoint());
                _drawings["craneRedComp"]->moveTo(comp->getPoint());
                if (_context->getGame().hasCurrentPiece())
                {
                    if (comp->getDrawing2() != nullptr)
                    {
                        std::string name = _context->getGame().getCurrentPiece().getId();
                        {
                            _drawings[name]->removeActions(RailsUtil::Action::CAN_MOVE);
                            _drawings[name]->addActions(RailsUtil::Action::ATTACH);
                            comp->setDrawings(_drawings["craneGreenComp"], nullptr);
                            _context->getGame().currentToStack();

                            _stackCounter++;
                        }
                    }
                }
                else
                {
                    if (_context->getGame().stackToCurrent())
                    {
                        std::string name = _context->getGame().getCurrentPiece().getId();

                        _drawings[name]->addActions(RailsUtil::Action::CAN_MOVE);
                        _drawings[name]->removeActions(RailsUtil::Action::ATTACH);
                        comp->setDrawings(_drawings["craneRedComp"], _drawings[name]);

                        _stackCounter--;
                    }
                }
                comp->setActive(true);
                _animation = RailsUtil::Animation::NONE;
            }
        }
        break;
    case RailsUtil::Animation::GO_TO_STACK:
        if (_drawings["craneComposing"]->getPoint().X > 234)
            _drawings["craneComposing"]->move(Point(-Config::PositionIncrement, 0));
        else
            _animation = RailsUtil::Animation::NONE;
        break;
    case RailsUtil::Animation::GO_TO_QUEUE:
        if (_drawings["craneComposing"]->getPoint().X < 499)
            _drawings["craneComposing"]->move(Point(Config::PositionIncrement, 0));
        else if (_drawings["craneComposing"]->getPoint().X > 499)
            _drawings["craneComposing"]->move(Point(-Config::PositionIncrement, 0));
        else
            _animation = RailsUtil::Animation::NONE;
        break;
    case RailsUtil::Animation::MOVE_WAGONS:
    {
        if (_context->getGame().hasCurrentPiece())
        {
            std::string name = _context->getGame().getCurrentPiece().getId();
            int actions = _drawings[name]->getActions();
            if (RailsUtil::isFlagSet(actions, RailsUtil::Action::CAN_MOVE))
            {

                if (_drawings[name]->getPoint().X < 499)
                {
                    _drawings[name]->move(Point(Config::PositionIncrement,0));
                }
                else
                {
                    _animation = RailsUtil::Animation::NONE;
                    requestOpposite("light1N");
                }
            }
        }
        break;
    }


    case RailsUtil::Animation::GO_TO_OUTPUT:
        Piece current = _context->getGame().getCurrentPiece();
        if (current.getValue() != -1)
        {
            if (canMove(_drawings[current.getId()]))
            {
                _drawings[current.getId()]->move(Point(Config::PositionIncrement,0));
                //break;
            }
            else
            {
                requestOpposite("light2N");
                _context->getGame().currentToOutput();
                _animation = RailsUtil::Animation::NONE;
                //break;
            }
        }
        break;
    }
}
bool rails::PlayScreen::canMove(IDrawing* d)
{
    if (RailsUtil::isFlagSet(d->getActions(), RailsUtil::Action::CANT_COLLIDE))
    {
        for (auto &drawing : _drawings)
        {
            if (drawing.second == d || !drawing.second->isActive())
                continue;

            if ( RailsUtil::isFlagSet(drawing.second->getActions(), RailsUtil::Action::CANT_COLLIDE))
            {
                if (d->checkCollision(drawing.second))
                    return false;
            }
        }
    }

    return true;
}

bool rails::PlayScreen::drawingEvent(std::pair<std::string, IDrawing*> drawing, rails::RailsUtil::EventType event)
{
    if (Screen::drawingEvent(drawing, event))
        return true;

    if (drawing.second->isActive())
    {
        int flag = drawing.second->getActions();
        if (event == rails::RailsUtil::EventType::LEFT_KEY)
        {
            if (RailsUtil::isFlagSet(flag, RailsUtil::Action::ON_LEFT_KEY))
            {
                drawing.second->move(Point(-Config::PositionIncrement, 0));
                if (!canMove(drawing.second))
                {
                    drawing.second->move(Point(Config::PositionIncrement, 0));
                }
                return true;
            }
        }
        else if (event == rails::RailsUtil::EventType::LEFT_CLICK)
        {
            if (RailsUtil::isFlagSet(flag, RailsUtil::Action::IMPOSSIBLE_GAME))
            {
                if (!_context->getGame().hasFinished())
                    _context->getGame().answerImpossibleGame();
                return true;
            }
        }
        else if (event == rails::RailsUtil::EventType::RIGHT_KEY)
        {
            if (RailsUtil::isFlagSet(flag, RailsUtil::Action::ON_RIGHT_KEY))
            {
                drawing.second->move(Point(Config::PositionIncrement, 0));
                if (!canMove(drawing.second))
                    drawing.second->move(Point(-Config::PositionIncrement, 0));
                return true;
            }
        }
        else if (event == rails::RailsUtil::EventType::UP_KEY)
        {
            if (RailsUtil::isFlagSet(flag, RailsUtil::Action::ON_UP_KEY))
            {
                drawing.second->move(Point(0, -Config::PositionIncrement));
                if (!canMove(drawing.second))
                {
                    drawing.second->move(Point(0, Config::PositionIncrement));
                }

                return true;
            }
        }
    }

    return false;
}

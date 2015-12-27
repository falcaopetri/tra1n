/*
    Rails
    ED - 2015/1
    UFSCar - S�o Carlos
*/
#include "RailsGUI.h"

rails::RailsGUI::RailsGUI()
{
    status = 12;
}

rails::RailsGUI::~RailsGUI()
{
}

void rails::RailsGUI::changeToScreen(Config::Screen screenID)
{
    if (_currentScreen)
        _currentScreen->reset();
    if (screenID == Config::Screen::PLAY)
    {
        if (status == 12)
        {
            setSound(RailsUtil::Sound::PLAYING);
            playSound(RailsUtil::Sound::SHOCK);

            _currentScreen = getScreen(Config::Screen::PLAY_OFF);
            status = 1;

            _game.newGame();
            for (int i = 0; i < _game.piecesAmount(); ++i)
            {
                std::string wagon = "wagon" + std::to_string(i);
                _game.insertPiece(Piece(i+1, wagon));
                getScreen(Config::Screen::PLAY)->getDrawing(wagon)->setActive(true);
            }
            _game.generateLevel();

            int pos = 820 + 27 * _game.piecesAmount();
            for (int i = 0; i < _game.piecesAmount(); ++i)
            {
                pos -= 27;

                std::string imageName = "tn" + std::to_string(_game.getOutput().at(i).getValue());
                loadSystemImage(imageName, pos, 417, 0, true);
            }
        }
    }
    else if (screenID == Config::Screen::PLAY_OFF)
    {
    }
    else if (screenID == Config::Screen::ABOUT)
    {
        _currentScreen = getScreen(screenID);
    }
    else if (screenID == Config::Screen::HOME)
    {
        status = 12;
        setSound(RailsUtil::Sound::INTRO);

        resetPositions();
        if (!_game.hasFinished())
        {
            _game.finishGame();
        }

        _currentScreen = getScreen(screenID);
    }
    else if (screenID == Config::Screen::HOWTO)
    {
        _currentScreen = getScreen(screenID);
    }
}

Screen* rails::RailsGUI::getScreen(Config::Screen screenID)
{
    if (screens[screenID] == nullptr)
    {
        if (screenID == Config::Screen::PLAY)
        {
            screens[screenID] = new PlayScreen(this);
        }
        else
        {
            screens[screenID] = new Screen(this);
        }
    }

    return screens[screenID];
}

void rails::RailsGUI::raiseError(std::string message, RailsUtil::ErrorType type)
{
    RailsUtil::printError(message.c_str());
    _exitCode = type;
    shutdown();
    throw std::runtime_error(message);
}

/*
Carrega uma imagem utilizada pelo jogo, cujo path encontra-se
em Config::imagesPaths
*/
bool rails::RailsGUI::loadSystemImage (std::string name, int xPos, int yPos, int actions, bool isactive = true, std::string bitmapName)
{
    if (systemImages[name] == nullptr)
    {
        Drawing* d;
            if (bitmapName == "")
                d = new Drawing(Point(xPos, yPos), al_load_bitmap(Config::systemPaths[name]), actions, isactive);
        else
            d = new Drawing(Point(xPos, yPos), al_load_bitmap(Config::systemPaths[bitmapName]), actions, isactive);

        if(d->getBitmap() == nullptr)
        {
            raiseError("failed to load " + name + " image", RailsUtil::ErrorType::BITMAP);
            return false;
        }

        systemImages[name] = d;
    }
    else
    {
        systemImages[name]->removeActions(0x11111111);
        systemImages[name]->addActions(actions);
        systemImages[name]->moveTo(Point(xPos, yPos));
        systemImages[name]->setActive(isactive);
    }

    return true;
}
void rails::RailsGUI::addImageToScreen(std::string name, Config::Screen screen, bool visible = true)
{
    if (systemImages.find(name) != systemImages.end())
    {
        getScreen(screen)->addDrawing(name, systemImages[name], visible);
    }
}
void rails::RailsGUI::removeImageFromScreen(std::string name, Config::Screen screen)
{
    getScreen(screen)->removeDrawing(name);
}

void rails::RailsGUI::playSound(RailsUtil::Sound sound)
{
    if (soundOn)
        al_play_sample(sounds[sound], 2.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);

}

void rails::RailsGUI::setSound(RailsUtil::Sound sound)
{
    if (sound != _currentSound)
    {
        _currentSound = sound;
        if (isPlayingSound)
        {
            switchSound();
            switchSound();
        }
    }
}
void rails::RailsGUI::switchSound()
{
    if (!soundOn)
    {
        if (!isPlayingSound)
        {
            al_play_sample(sounds[_currentSound], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &_musicId);
            soundOn = isPlayingSound = true;
        }
    }
    else
    {
        if (isPlayingSound)
        {
            al_stop_sample(&_musicId);
            soundOn = isPlayingSound = false;
        }
    }
}

std::string rails::RailsGUI::getOppositeImage(std::string name)
{
    if (name[name.length()-1] == 'F')
    {
        name.replace(name.end()-1, name.end(), "N");
    }
    else if (name[name.length()-1] == 'N')
    {
        name.replace(name.end()-1, name.end(), "F");
    }
    return name;
}
rails::IDrawing* rails::RailsGUI::requestImage(std::string name)
{
    return systemImages[name];
}

/*
    Inicializa o Allegro e todos os componentes utilizados
    Inicializa todas as imagens utilizadas ao longo do jogo
*/
void rails::RailsGUI::initAllegro ()
{
    // Init
    {
        if(!al_init())
        {
            raiseError("failed to initialize allegro!\n", RailsUtil::ErrorType::ALLEGRO);
        }
    }

    RailsUtil::setResourceArchive();


    // Keyboard
    {
        if(!al_install_keyboard())
        {
            raiseError("failed to initialize the keyboard!\n", RailsUtil::ErrorType::ADDON);
        }
    }
    // Mouse
    {
        if(!al_install_mouse())
        {
            raiseError("failed to initialize the mouse!\n", RailsUtil::ErrorType::ADDON);
        }
    }
    // Timers
    {
        _timerDrawing = al_create_timer(1.0 / Config::FPS);
        if(!_timerDrawing)
        {
            raiseError("failed to create timerDrawing!\n", RailsUtil::ErrorType::TIMER);
        }
        _timerPlaying = al_create_timer(1.0);
        if(!_timerPlaying)
        {
            raiseError("failed to create timerPlaying!\n", RailsUtil::ErrorType::TIMER);
        }
        _timerAnimation = al_create_timer(1.0 * 5 *2 / Config::FPS);
        if(!_timerAnimation)
        {
            raiseError("failed to create timerAnimation!\n", RailsUtil::ErrorType::TIMER);
        }
    }
    // Display
    {
        _display = al_create_display(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
        if(!_display)
        {
            raiseError("failed to create display!\n", RailsUtil::ErrorType::ALLEGRO);
        }
    }

    // Font
    {
        al_init_font_addon();
        if(!al_init_ttf_addon())
        {
            raiseError("failed to initialize the ttf addon!\n", RailsUtil::ErrorType::ADDON);
        }

        _font = al_load_ttf_font(Config::systemPaths["fontPath"], 50, 0);
        if(!_font)
        {
            raiseError("failed to initialize the ttf font!\n", RailsUtil::ErrorType::ADDON);
        }
    }
    // Audio
    {
        if(!al_install_audio())
        {
            raiseError("failed to initialize audio!\n", RailsUtil::ErrorType::AUDIO);
        }
        if(!al_init_acodec_addon())
        {
            raiseError("failed to initialize audio codecs!\n", RailsUtil::ErrorType::AUDIO);
        }

        if (!al_reserve_samples(2))
        {
            raiseError("failed to reserve samples!\n", RailsUtil::ErrorType::AUDIO);
        }
        sounds[RailsUtil::Sound::INTRO] = al_load_sample(Config::systemPaths["soundPathIntro"]);

        if (!sounds[RailsUtil::Sound::INTRO])
        {
            raiseError("failed to load audio clip sample!\n" , RailsUtil::ErrorType::AUDIO);
        }

        sounds[RailsUtil::Sound::PLAYING] = al_load_sample(Config::systemPaths["soundPathPlaying"]);

        if (!sounds[RailsUtil::Sound::PLAYING])
        {
            raiseError("failed to load audio clip sample!\n" , RailsUtil::ErrorType::AUDIO);
        }

        sounds[RailsUtil::Sound::DOWNS] = al_load_sample(Config::systemPaths["soundDown"]);

        if (!sounds[RailsUtil::Sound::DOWNS])
        {
            raiseError("failed to load audio clip sample!\n" , RailsUtil::ErrorType::AUDIO);
        }

        sounds[RailsUtil::Sound::UPS] = al_load_sample(Config::systemPaths["soundUp"]);
        if (!sounds[RailsUtil::Sound::UPS])
        {
            raiseError("failed to load audio clip sample!\n" , RailsUtil::ErrorType::AUDIO);
        }

        sounds[RailsUtil::Sound::TRAIN] = al_load_sample(Config::systemPaths["soundTrain"]);
        if (!sounds[RailsUtil::Sound::TRAIN])
        {
            raiseError("failed to load audio clip sample!\n" , RailsUtil::ErrorType::AUDIO);
        }

        sounds[RailsUtil::Sound::SHOCK] = al_load_sample(Config::systemPaths["soundShock"]);
        if (!sounds[RailsUtil::Sound::SHOCK])
        {
            raiseError("failed to load audio clip sample!\n" , RailsUtil::ErrorType::AUDIO);
        }
    }
    // Image Addon
    {
        if(!al_init_image_addon())
        {
            raiseError("failed to initialize image addon!", RailsUtil::ErrorType::BITMAP);
        }
    }

    std::string imageName;
    // Backgrounds
    {
        imageName = "aaabackgroundMenu";
        loadSystemImage(imageName, 0, 0, 0);
        addImageToScreen(imageName, Config::Screen::HOME);
        addImageToScreen(imageName, Config::Screen::PLAY);
        addImageToScreen(imageName, Config::Screen::ABOUT);


        imageName = "aaabackgroundF";
        loadSystemImage(imageName, 0, 0, 0);
        addImageToScreen(imageName, Config::Screen::PLAY_OFF);
        addImageToScreen(imageName, Config::Screen::HOWTO);

        imageName = "aaabackgroundO";
        loadSystemImage(imageName, 0, 0, 0);
        addImageToScreen(imageName, Config::Screen::PLAY);
    }
    // Icon
    {
        imageName = "icon";
        loadSystemImage(imageName, 0, 0, 0);
    }
    // Start Button
    {
        imageName = "startF";
        loadSystemImage(imageName, 405, 263, RailsUtil::Action::MOUSE_OVER);
        addImageToScreen(imageName, Config::Screen::HOME);

        imageName = "startN";
        loadSystemImage(imageName, 399, 257, RailsUtil::Action::GOTO_PLAY | RailsUtil::Action::MOUSE_EXIT);
    }

    // How to play Button
    {
        imageName = "howToPlayF";
        loadSystemImage(imageName, 432, 355, RailsUtil::Action::MOUSE_OVER);
        addImageToScreen(imageName, Config::Screen::HOME);

        imageName = "howToPlayN";
        loadSystemImage(imageName, 426, 350, RailsUtil::Action::GOTO_HOWTO | RailsUtil::Action::MOUSE_EXIT);
    }
    // How To Play Full
    {
        imageName = "howPlayFull";
        loadSystemImage(imageName, 0, 0, 0);
        addImageToScreen(imageName, Config::Screen::HOWTO);
    }

    // Impossible Button
    {
        imageName = "impossibleF";
        loadSystemImage(imageName, 761, 49, RailsUtil::Action::MOUSE_OVER);
        addImageToScreen(imageName, Config::Screen::PLAY);

        imageName = "impossibleN";
        loadSystemImage(imageName, 754, 42, RailsUtil::Action::IMPOSSIBLE_GAME | RailsUtil::Action::MOUSE_EXIT);
        //addImageToScreen(imageName, Config::Screen::HOME);
    }
    // About Button
    {
        imageName = "aboutF";
        loadSystemImage(imageName, 522, 445, RailsUtil::Action::MOUSE_OVER);
        addImageToScreen(imageName, Config::Screen::HOME);

        imageName = "aboutN";
        loadSystemImage(imageName, 517, 440, RailsUtil::Action::GOTO_ABOUT | RailsUtil::Action::MOUSE_EXIT);
    }

    // Sound Button
    {
        imageName = "soundN";
        loadSystemImage(imageName, 1150, 10, RailsUtil::Action::SOUND);
        addImageToScreen(imageName, Config::Screen::HOME);
        addImageToScreen(imageName, Config::Screen::PLAY);
        addImageToScreen(imageName, Config::Screen::ABOUT);
        addImageToScreen(imageName, Config::Screen::HOWTO);

        imageName = "soundF";
        loadSystemImage(imageName, 1150, 10, RailsUtil::Action::SOUND);
    }
    // sliderSeparator
    {
        imageName = "sliderSeparator";
        loadSystemImage(imageName, 444, 565, 0);
        addImageToScreen(imageName, Config::Screen::HOWTO);
    }
    // Sound Button
    {
        imageName = "zhowPlayBig";
        loadSystemImage(imageName, 387, 20, 0);
        addImageToScreen(imageName, Config::Screen::HOWTO);
    }

    // Answer Image
    {
        imageName = "correctAnswer";
        loadSystemImage(imageName, 331, 222, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, false);

        imageName = "cincorrectAnswer";
        loadSystemImage(imageName, 278, 222, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, false);
    }
    // placas
    {
        imageName = "tn1";
        loadSystemImage(imageName, 817, 414, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, true);
        imageName = "tn2";
        loadSystemImage(imageName, 843, 843, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, true);
        imageName = "tn3";
        loadSystemImage(imageName, 869, 414, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, true);
        imageName = "tn4";
        loadSystemImage(imageName, 896, 414, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, true);
        imageName = "tn5";
        loadSystemImage(imageName, 923, 414, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, true);
    }
    // Station
    {
        imageName = "station";
        loadSystemImage(imageName, 794, 438, 0);
        addImageToScreen(imageName, Config::Screen::PLAY);
    }
    // Locomotive
    {
        imageName = "loco";
        loadSystemImage(imageName, 1090, 531, RailsUtil::Action::CANT_COLLIDE |
                        RailsUtil::Action::CANT_GO_OUT);
        addImageToScreen(imageName, Config::Screen::PLAY);
    }
    // Plataforma
    {
        imageName = "platform";
        loadSystemImage(imageName, 27, 427, /*RailsUtil::Action::CANT_COLLIDE |*/
                        RailsUtil::Action::CANT_GO_OUT);
        addImageToScreen(imageName, Config::Screen::PLAY);
    }
    // sinaleiros
    {
        imageName = "light1N";
        loadSystemImage(imageName, 470, 535, /*RailsUtil::Action::CANT_COLLIDE |*/
                        RailsUtil::Action::CANT_GO_OUT);
        addImageToScreen(imageName, Config::Screen::PLAY, false);
        imageName = "light2N";
        loadSystemImage(imageName, 611, 535, /*RailsUtil::Action::CANT_COLLIDE |*/
                        RailsUtil::Action::CANT_GO_OUT);
        addImageToScreen(imageName, Config::Screen::PLAY, false);

        imageName = "light1F";
        loadSystemImage(imageName, 470, 529, /*RailsUtil::Action::CANT_COLLIDE |*/
                        RailsUtil::Action::CANT_GO_OUT);
        addImageToScreen(imageName, Config::Screen::PLAY);
        imageName = "light2F";
        loadSystemImage(imageName, 611, 529, /*RailsUtil::Action::CANT_COLLIDE |*/
                        RailsUtil::Action::CANT_GO_OUT);
        addImageToScreen(imageName, Config::Screen::PLAY);
    }

    // Images
    {
        imageName = "wagon";
        loadSystemImage(imageName, 239, 435, RailsUtil::Action::CANT_COLLIDE );
        addImageToScreen(imageName, Config::Screen::PLAY, true);
        for (int i = 0; i < _game.piecesAmount(); ++i)
        {
            imageName = "wagon";
            imageName += std::to_string(i);
            loadSystemImage(imageName, 363+90*-i, 517, RailsUtil::Action::CANT_COLLIDE |
                            RailsUtil::Action::CANT_GO_OUT |
                            RailsUtil::Action::CAN_MOVE |
                            RailsUtil::Action::ATTACH );
            addImageToScreen(imageName, Config::Screen::PLAY, false);
        }
    }
    // Images
    {
        for (int i = 0; i < 5; ++i)
        {
            imageName = "sliderNode";
            std::string imageNameN = imageName + std::to_string(i) + "N";

            loadSystemImage(imageNameN, 410+87*i, 553, 0, i == 0, imageName+"N");
            addImageToScreen(imageNameN, Config::Screen::HOWTO, i == 0);

            imageNameN = imageName + std::to_string(i) + "F";
            loadSystemImage(imageNameN, 410+87*i, 553, 0, true, imageName+"F");
            addImageToScreen(imageNameN, Config::Screen::HOWTO, true);
        }

    }
    // Arrows
    {
        imageName = "left";
        loadSystemImage(imageName, 23, 262, RailsUtil::Action::HOWTO_PREV);
        addImageToScreen(imageName, Config::Screen::HOWTO, false);

        imageName = "right";
        loadSystemImage(imageName, 1130, 262, RailsUtil::Action::HOWTO_NEXT);
        addImageToScreen(imageName, Config::Screen::HOWTO);
    }
    // aboutInfo
    {
        imageName = "aboutInfo";
        loadSystemImage(imageName, 0, 0, 0);
        addImageToScreen(imageName, Config::Screen::ABOUT);
    }
    // Crane Green
    {
        imageName = "craneGreenComp";
        loadSystemImage(imageName, 499, -257, RailsUtil::Action::ON_DOWN_KEY |
                        RailsUtil::Action::ON_UP_KEY |
                        RailsUtil::Action::ON_RIGHT_KEY |
                        RailsUtil::Action::ON_LEFT_KEY |
                        RailsUtil::Action::CANT_COLLIDE |
                        RailsUtil::Action::ATTACH);
        addImageToScreen(imageName, Config::Screen::PLAY, false);
        addImageToScreen(imageName, Config::Screen::PLAY, false);

        imageName = "craneRedComp";
        loadSystemImage(imageName, 499, -257, RailsUtil::Action::ON_DOWN_KEY |
                        RailsUtil::Action::ON_UP_KEY |
                        RailsUtil::Action::ON_RIGHT_KEY |
                        RailsUtil::Action::ON_LEFT_KEY |
                        RailsUtil::Action::CANT_COLLIDE |
                        RailsUtil::Action::ATTACH);
        addImageToScreen(imageName, Config::Screen::PLAY, false);

        ComposedDrawing* comp = new ComposedDrawing();
        comp->setDrawings(systemImages["craneGreenComp"], nullptr);
        imageName = "craneComposing";
        systemImages[imageName] = comp;
        addImageToScreen(imageName, Config::Screen::PLAY, true);


    }
    // Back
    {
        imageName = "zback";
        loadSystemImage(imageName, 20, 10, RailsUtil::Action::GOTO_HOME);
        addImageToScreen(imageName, Config::Screen::ABOUT);
        addImageToScreen(imageName, Config::Screen::PLAY);
        addImageToScreen(imageName, Config::Screen::HOWTO);
    }
    // Event Queue
    {
        _eventQueue = al_create_event_queue();
        if(!_eventQueue)
        {
            raiseError("failed to create _eventQueue!\n", RailsUtil::ErrorType::ALLEGRO);
        }
    }
    // Window properties
    {
        al_set_window_title(_display, Config::windowTitle);
        al_set_display_icon(_display, ((Drawing*)systemImages["icon"])->getBitmap());

        //al_set_display_flag(_display, ALLEGRO_FULLSCREEN_WINDOW, true);
    }
    // Event registers
    {
        al_register_event_source(_eventQueue, al_get_display_event_source(_display));
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timerDrawing));
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timerPlaying));
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timerAnimation));
        al_register_event_source(_eventQueue, al_get_keyboard_event_source());
        al_register_event_source(_eventQueue, al_get_mouse_event_source());
    }
    // Display setup
    {
        al_set_target_bitmap(al_get_backbuffer(_display));
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
    }
    // Start timers
    {
        al_start_timer(_timerDrawing);
        al_start_timer(_timerPlaying);
        al_start_timer(_timerAnimation);
    }

    changeToScreen(Config::Screen::HOME);

    setSound(RailsUtil::Sound::INTRO);
    switchSound();
    _exitCode = 0;
}

void rails::RailsGUI::resetPositions ()
{
    std::string imageName;
    // Images
    {
        for (int i = 0; i < _game.piecesAmount(); ++i)
        {
            imageName = "wagon";
            imageName += std::to_string(i);
            loadSystemImage(imageName, 363+90*-i, 517, RailsUtil::Action::CANT_COLLIDE |
                            RailsUtil::Action::CANT_GO_OUT |
                            RailsUtil::Action::CAN_MOVE |
                            RailsUtil::Action::ATTACH );
        }
    }

    // Crane Green
    {
        imageName = "craneGreenComp";
        loadSystemImage(imageName, 499, -257, RailsUtil::Action::ON_DOWN_KEY |
                        RailsUtil::Action::ON_UP_KEY |
                        RailsUtil::Action::ON_RIGHT_KEY |
                        RailsUtil::Action::ON_LEFT_KEY |
                        RailsUtil::Action::CANT_COLLIDE |
                        RailsUtil::Action::ATTACH, false);

        imageName = "craneRedComp";
        loadSystemImage(imageName, 499, -257, RailsUtil::Action::ON_DOWN_KEY |
                        RailsUtil::Action::ON_UP_KEY |
                        RailsUtil::Action::ON_RIGHT_KEY |
                        RailsUtil::Action::ON_LEFT_KEY |
                        RailsUtil::Action::CANT_COLLIDE |
                        RailsUtil::Action::ATTACH, false);
    }
    // crane Composing
    {
        imageName = "craneComposing";
        systemImages[imageName]->moveTo(Point(499, -258));
    }

}

void rails::RailsGUI::loop ()
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(_eventQueue, &ev);

    if(ev.type == ALLEGRO_EVENT_TIMER)
    {
        if (ev.timer.source == _timerDrawing)
        {
            redraw = true;
        }
        else if (ev.timer.source == _timerAnimation)
        {
            if (!_game.hasFinished())
            {
                if (status < 9)
                {
                    status++;
                }
                else if (status == 9)
                {
                    _currentScreen = getScreen(Config::Screen::PLAY);
                    status = 10;
                }
                else if (status == 10)
                {
                    _currentScreen = getScreen(Config::Screen::PLAY_OFF);
                    status = 11;
                }
                else if (status == 11)
                {
                    _currentScreen = getScreen(Config::Screen::PLAY);
                    _game.resetScore();
                    status = 12;
                }
            }
        }
        else if (ev.timer.source == _timerPlaying)
        {
            if (!_game.hasFinished() && status == 12)
            {
                _game.decrementTimer();
            }
        }
    }

    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        _exitCode = 1;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_ESCAPE:
            if (!_game.hasFinished())
                _game.finishGame();

            changeToScreen(Config::Screen::HOME);
            break;
        }
    }


    _currentScreen->checkEvents(ev);
    if(redraw && al_is_event_queue_empty(_eventQueue))
    {
        redraw = false;
        al_clear_to_color(al_map_rgb(0,0,0));
        _currentScreen->recalculate();
        _currentScreen->draw();
        al_flip_display();
    }
}
/*
    Destr�i todos os componentes do Allegro
    Deve-se adicionar � esse m�todos qualquer componente do Allegro
    que necessite de uma desreferencia��o apropriada

    Essa fun��o � executada ao final do jogo ou caso a inicializa��o
    do Allegro falhe logo no in�cio da aplica��o
*/
void rails::RailsGUI::shutdown ()
{
    if (_timerDrawing)    al_destroy_timer(_timerDrawing);
    if (_timerPlaying)    al_destroy_timer(_timerPlaying);
    if (_timerAnimation)    al_destroy_timer(_timerAnimation);
    if (_display)         al_destroy_display(_display);
    if (_eventQueue)     al_destroy_event_queue(_eventQueue);
    for (auto &s: sounds)
    {
        if (s.second)
            al_destroy_sample(s.second);
    }
    for (auto &image: systemImages)
    {
        image.second->destroy();
    }
    systemImages.clear();

    for (auto &screen: screens)
    {
        delete screen.second;
    }
    screens.clear();

}


int rails::RailsGUI::exitCode()
{
    return _exitCode;
}

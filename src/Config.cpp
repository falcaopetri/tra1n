/*
    Rails
    ED - 2015/1
    UFSCar - S�o Carlos
*/
#include "Config.h"

const float rails::Config::FPS = 60*2;

const int rails::Config::SCREEN_WIDTH = 1200;
const int rails::Config::SCREEN_HEIGHT = 600;
const int rails::Config::PositionIncrement = 5;

const char* rails::Config::windowTitle = "Rails";

std::map<std::string, char*> rails::Config::systemPaths =
{
    { "soundPathPlaying", "sounds/soundPlaying.wav"},
    { "soundPathIntro", "sounds/soundIntro.wav"},
    { "soundUp", "sounds/up.wav"},
    { "soundDown", "sounds/down.wav"},
    { "soundTrain", "sounds/train.wav"},
    { "soundShock", "sounds/shock.wav"},

    { "fontPath", "fonts/badabb.ttf"},
    { "dataFile", "data.dat"},

    { "left",            "images/statics/left.png"},
    { "right",            "images/statics/right.png"},
    { "howPlayFull",            "images/movables/howPlayFull.png"},
    { "sliderNodeF",            "images/movables/sliderNodeF.png"},
    { "sliderNodeN",            "images/movables/sliderNodeN.png"},

    { "sliderSeparator",            "images/statics/sliderSeparator.png"},
    { "zhowPlayBig",            "images/statics/howPlayBig.png"},

    { "aaabackgroundMenu",   "images/statics/aaBackgroundMenu.png"},
    { "aaabackgroundF",   "images/statics/aaBackgroundF.png"},
    { "aaabackgroundO",   "images/statics/aaBackgroundO.png"},

    { "logo",            "images/statics/logo.png"},
    { "icon",            "images/system/icon.png" },

    { "correctAnswer",   "images/statics/correctAnswer.png" },
    { "cincorrectAnswer",     "images/statics/incorrectAnswer.png" },

    { "startF",   "images/statics/startF.png" },
    { "startN",     "images/statics/startN.png" },

    { "howToPlayF",   "images/statics/howToPlayF.png" },
    { "howToPlayN",     "images/statics/howToPlayN.png" },

    { "impossibleF",   "images/statics/impossibleF.png" },
    { "impossibleN",     "images/statics/impossibleN.png" },

    { "tn1",     "images/statics/n1.png" },
    { "tn2",     "images/statics/n2.png" },
    { "tn3",     "images/statics/n3.png" },
    { "tn4",     "images/statics/n4.png" },
    { "tn5",     "images/statics/n5.png" },

    { "aboutF",   "images/statics/aboutF.png" },
    { "aboutN",     "images/statics/aboutN.png" },

    { "soundF",       "images/statics/soundF.png" },
    { "soundN",        "images/statics/soundN.png" },

    { "easyNoFocus",    "images/system/easyNoFocus.png" },
    { "easyFocus",      "images/system/easyFocus.png" },

    { "mediumNoFocus",  "images/system/mediumNoFocus.png" },
    { "mediumFocus",    "images/system/mediumFocus.png" },

    { "hardNoFocus",    "images/system/hardNoFocus.png" },
    { "hardFocus",      "images/system/hardFocus.png" },

    { "insaneNoFocus",  "images/system/insaneNoFocus.png" },
    { "insaneFocus",    "images/system/insaneFocus.png" },

    { "aboutInfo",      "images/system/aboutInfo.jpg" },
    { "zback",           "images/statics/close.png" },

    { "craneGreenComp",           "images/movables/craneGreen.png" },
    { "craneYellowComp",           "images/movables/craneYellow.png" },
    { "craneRedComp",           "images/movables/craneRed.png" },

    { "station",           "images/statics/station.png" },
    { "platform",           "images/statics/platform.png" },
    { "loco",           "images/movables/loco.png" },

    { "light1N",           "images/statics/lightGreen.png" },
    { "light1F",           "images/statics/lightRed.png" },
    { "light2N",           "images/statics/lightGreen.png" },
    { "light2F",           "images/statics/lightRed.png" },

    { "wagon",           "images/movables/wagon.png" },
    { "wagon0",           "images/movables/wagon0.png" },
    { "wagon1",           "images/movables/wagon1.png" },
    { "wagon2",           "images/movables/wagon2.png" },
    { "wagon3",           "images/movables/wagon3.png" },
    { "wagon4",           "images/movables/wagon4.png" },

    { "piece0", "images/image0.png"},
    { "piece1", "images/image1.png"},
    { "piece2", "images/image2.png"},
    { "piece3", "images/image3.png"}

};

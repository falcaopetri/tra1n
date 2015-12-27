/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Score.h"

rails::Score::Score() {
    reset();
}


void rails::Score::reset() {
	_timing = 60;
}

void rails::Score::decrementTimer() {
	_timing--;
}

unsigned rails::Score::getTiming() {
	return _timing;
}

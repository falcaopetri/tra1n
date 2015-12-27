/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef SCORE_H
#define SCORE_H

#include <string>

namespace rails {
	class Score {
	private:
		unsigned _timing;
		unsigned _errorCounter;
	public:
	    Score();
		void reset();
		/*
			Decrementa o timing em 1 segundo
		*/
		void decrementTimer();

		unsigned getTiming();
		unsigned getErrorCounter();
	};
}

#endif

/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/

#ifndef GAME_H
#define GAME_H

#include "Config.h"
#include "Piece.h"
#include "Score.h"

#include "Deque.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "RailsUtil.hpp"

#include <iostream>

using namespace rails;

namespace rails {
	class Game {
	private:
		/*
			Dificuldade do jogo atual
		*/
		int _level;
		/*
			Score atual
		*/
		Score _score;

		Queue<Piece> _queue;
		Stack<Piece> _stack;
		Deque<Piece> _output;

		Deque<Piece> _simulateInput;
		Deque<Piece> _simulateOutput;

		bool _isCurrentGamePossible;

		Piece _currentPiece;

		bool _hasFinished;

        void randomShuffle();

        void analyseAnswer();

        bool _isCorrect;
	public:
		Game();

		int piecesAmount();

        bool queueToCurrent();
		bool currentToStack();
		bool stackToCurrent();
		bool currentToOutput();

		Piece getCurrentPiece();
		bool hasCurrentPiece();

    	void nextLevel();

		bool hasFinished();
        bool isCorrect();

		void resetScore();

        Deque<Piece>& getOutput();

        void simulate();

		void generateLevel();
		/*
			Prepara o Game para um novo jogo
			Retorna a primeira peça do jogo
		*/
		void newGame();

		void insertPiece(Piece p);

		bool answerImpossibleGame();

		void decrementTimer();
		Score getScore();
		/*
			Encerra o jogo, validando se ele já tinha chegado ao final
			e adicionando a pontuação do jogador, se for o caso
		*/
		bool finishGame();
	};
}

#endif

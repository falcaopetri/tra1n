/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Game.h"

Game::Game()
{
    _level = 5;
}

void Game::insertPiece(Piece p)
{
    _queue.push(p);
    _simulateInput.pushBack(p);

    _output.pushBack(p);
    _simulateOutput.pushBack(p);
}
bool Game::queueToCurrent() {
    if(!_queue.empty() && _currentPiece.getValue() == -1) {
        _currentPiece = _queue.front();
        _queue.pop();
        return true;
    }
    return false;
}
bool Game::currentToStack() {
    if(_currentPiece.getValue() != -1) {
        _stack.push(_currentPiece);
        _currentPiece = Piece(-1, "");
        return true;
    }
    return false;
}
bool Game::stackToCurrent() {
    if(!_stack.empty() && _currentPiece.getValue() == -1) {
        _currentPiece = _stack.top();
        _stack.pop();

        return true;
    }
    return false;
}
void Game::analyseAnswer() {
    for (int i = 0; i < piecesAmount(); ++i) {
        if (_output.at(i) != _output.at(i+piecesAmount())) {
            _isCorrect = false;
            return;
        }

    }
    _isCorrect = true;
}
bool Game::isCorrect() {
    return _isCorrect;
}
bool Game::currentToOutput() {
    if(_currentPiece.getValue() != -1) {
        _output.pushBack(_currentPiece);
        _currentPiece = Piece(-1, "");

        if (_output.size() == 2*piecesAmount()) {
            analyseAnswer();
            finishGame();
        }
        return true;
    }
    return false;

}
Piece Game::getCurrentPiece() {
    return _currentPiece;
}

void Game::resetScore()
{
	return _score.reset();
}

void inline swap (Piece& p1, Piece& p2) {
    Piece pTmp = p1;
    p1 = p2;
    p2 = pTmp;
}
void Game::randomShuffle() {
    srand(time(NULL));

    for (int i = _output.size()-1; i > 0; --i) {
        int r = rand() % i;
        swap(_output.at(i), _output.at(r));
        swap(_simulateOutput.at(i), _simulateOutput.at(r));
    }
}
bool Game::hasCurrentPiece() {
    return _currentPiece.getValue() != -1;
}
void Game::generateLevel() {
    randomShuffle();
    simulate();
    _hasFinished = false;
    _currentPiece = Piece(-1, "");
}
void Game::simulate() {
    _isCurrentGamePossible = true;
    int pos = 0;

    while (!_simulateInput.empty()) {
        Piece wished = _simulateOutput.front(); _simulateOutput.popFront();

        if (wished < _simulateInput[pos]) {
            _isCurrentGamePossible = false;
            break;
        }
        else {
            while (wished != _simulateInput[pos]) {
                ++pos;
            }
            _simulateInput.erase(pos);
            pos--;
            if (pos < 0) pos = 0;
        }
    }
}
void Game::newGame()
{
    _level = 5;
    _currentPiece = Piece(-1, "");
}
void  Game::nextLevel() {
    //_level++;
    //if (_level == 6)
        finishGame();
}

Deque<Piece>& Game::getOutput() {
    return _output;
}

bool Game::answerImpossibleGame()
{
    if (!_isCurrentGamePossible) {
        nextLevel();
        _isCorrect = true;
        return true;
    }
    else {
        _isCorrect = false;
        finishGame();
        return false;
    }
}

int Game::piecesAmount() {
    return _level;
}

void Game::decrementTimer()
{
    if (_score.getTiming() == 0) {
        _isCorrect = false;
        finishGame();
    }
    else {
        _score.decrementTimer();
    }
}

Score Game::getScore()
{
    return _score;
}

bool Game::finishGame()
{
	if (hasFinished())
    {
        // nextLevel();
	}

    _hasFinished = true;

    while (!_queue.empty()) _queue.pop();
    while (!_stack.empty()) _stack.pop();
    while (!_output.empty()) _output.popFront();

    while (!_simulateOutput.empty()) _simulateOutput.popFront();
    while (!_simulateInput.empty()) _simulateInput.popFront();

	return true;
}

bool Game::hasFinished()
{
	return _hasFinished || (_queue.empty() && _stack.empty() && _currentPiece.getValue() == -1);
}

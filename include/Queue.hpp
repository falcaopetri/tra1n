/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Deque.hpp"

namespace rails {
    template <class T>
    class Queue {
    private:

    Deque<T> _deque;

    public:
		Queue(); //construtor
		~Queue (); //metodo destruidor
        bool push(T); //insere elemento no final da fila, usa pushBack do deque
        void pop (); //remove primeiro elemento, usa popFront do deque
        T& front(); //mostra o primeiro elemento da fila, usa o front do deque
        bool empty(); //retorna verdadeiro se Fila estiver vazio, falso caso contrario, usa o empty do deque
    };

    template <class T>
	rails::Queue<T>::Queue() {
	}
	template <class T>
	rails::Queue<T>::~Queue() {
	}

	template <class T>
	void rails::Queue<T>::pop() {
		_deque.popFront();;
	}

	template <class  T>
	bool rails::Queue<T>::push(T element){
		return _deque.pushBack(element);
  	}

	template <class T>
	T& rails::Queue<T>::front(){
		return _deque.front();

	}

	template <class T>
	bool rails::Queue<T>::empty() {
		return _deque.empty();
	}

}
#endif

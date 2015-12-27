/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef DEQUE_HPP
#define DEQUE_HPP

#define LAST (_header->left)
#define FIRST (_header->right)

#define NEW_LAST_ON_PUSH (LAST->right)
#define NEW_FIRST_ON_PUSH (FIRST->left)

#define NEW_LAST_ON_POP (LAST->left)
#define NEW_FIRST_ON_POP (FIRST->right)

namespace rails {
    template <class T>
    class Deque {
    private:

    class Node {
    public:
        T item;
        Node *right;
        Node *left;

    };

    Node *_header;
    unsigned int _size;

    public:
        Deque(); //construtor
        ~Deque (); //metodo destruidor
        bool pushFront(T); //insere elemento no inicio da fila
        bool pushBack(T); //insere elemento no final da fila
        void popFront (); //remove primeiro elemento
        void popBack (); //remove ultimo elemento
        T& front(); //mostra o primeiro elemento da fila
        T& back(); //mostra o ultimo elemento da fila
        bool empty(); //retorna verdadeiro se Fila estiver vazio, falso caso contrario
        T& at(int pos);
        // TODO
        // Solução temporária. Viola o contrato de Deque
        void erase(int pos);
        unsigned int size();

        T& operator[](size_t pos)
        {
            return at(pos);
        }
    };
}

template <class T>
rails::Deque<T>::Deque () {
    _header = new Node(); //Cria primeiro nó
    FIRST = _header;
    LAST = _header;
    _header->item = T(-1, "");
    _size = 0;
}

template <class T>
rails::Deque<T>::~Deque () {
    while (!empty())
        popFront();

    delete (_header);
}

template <class T>
bool rails::Deque<T>::pushBack(T element) {
    NEW_LAST_ON_PUSH = new Node();

    NEW_LAST_ON_PUSH->left = LAST;
    NEW_LAST_ON_PUSH->right = _header;
    NEW_LAST_ON_PUSH->item = element;

    LAST = NEW_LAST_ON_PUSH;

    ++_size;
    return true;
}

template <class T>
bool rails::Deque<T>::pushFront(T element) {
    NEW_FIRST_ON_PUSH = new Node();

    NEW_FIRST_ON_PUSH->right = FIRST;
    NEW_FIRST_ON_PUSH->left = _header;
    NEW_FIRST_ON_PUSH->item = element;

    FIRST = NEW_FIRST_ON_PUSH;

    ++_size;
    return true;
}

template <class T>
void rails::Deque<T>::popFront() {
    if (!empty())
    {
        Node *remove = FIRST;

        NEW_FIRST_ON_POP->left = _header;
        FIRST = NEW_FIRST_ON_POP;

        --_size;
        delete (remove);
    }
}

template <class T>
void rails::Deque<T>::popBack() {
    if (!empty())
    {
        Node *remove = LAST;

        NEW_LAST_ON_POP->right = _header;
        LAST = NEW_LAST_ON_POP;

        --_size;
        delete (remove);
    }
}


template <class T>
T& rails::Deque<T>::back() {
    return LAST->item;
}

template <class T>
T& rails::Deque<T>::front() {
    return FIRST->item;
}
template <class T>
T& rails::Deque<T>::at(int pos) {
    Node* aux = _header;
    ++pos;
    while (pos--) {
        aux = aux->right;
    }
    return aux->item;
}
template <class T>
void rails::Deque<T>::erase(int pos) {
    Node* headerCopy = _header;

    Node* aux = _header;
    ++pos;
    while (pos--) {
        aux = aux->right;
    }

    _header = aux->left; // muda o "pivó" do pop
    popFront();

    _header = headerCopy;
}
template <class T>
unsigned int rails::Deque<T>::size() {
    return _size;
}

template <class T>
bool rails::Deque<T>::empty() {
    if (FIRST == _header)
        return true;
    else
        return false;
}

#endif

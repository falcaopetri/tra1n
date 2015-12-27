/*
    The Last: Too Fast
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef PIECE_H
#define PIECE_H

#include <string>

namespace rails {
	/*
		Encapsula uma "Peça" do jogo,
		representada por um identificador inteiro
	*/
	class Piece {
	private:
	    int _value;
		std::string _id;
	public:
	    Piece ();
		Piece (int value, std::string id);

        int getValue () const;

		std::string getId () const;
		void setId (std::string id);
		/*
			Retorna se duas Peças são iguais (mesmo ID)
		*/
		bool isEqual (const Piece& other) const;

		bool operator <(const Piece &b) const {
            return getValue() < b.getValue();
		}

		bool operator !=(const Piece &b) const {
		    return (*this < b) || (b < *this);
		}

		/*Piece(const Piece& rhs);
        Piece& operator=(const Piece& rhs);*/
	};
}

#endif

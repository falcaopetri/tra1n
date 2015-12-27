/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Piece.h"

rails::Piece::Piece()
    : Piece(-1, "")
{
}

rails::Piece::Piece(int value, std::string id)
	: _value(value), _id(id)
{
}
int rails::Piece::getValue() const {
	return _value;
}

std::string rails::Piece::getId() const {
	return _id;
}
void rails::Piece::setId (std::string id) {
    _id = id;
}

bool rails::Piece::isEqual (const rails::Piece &other) const {
    return (getId() == other.getId());
}

#include "pieces.h"

using namespace std;

Piece::Piece()
{
}

Piece::Piece(char name, int value)
{
    this->name = name;
    this->value = value;
}

bool Piece::operator==(Piece piece)
{
    return this->name == piece.name && this->value == piece.value;
}

char Piece::getName()
{
    return name;
}

int Piece::getValue()
{
    return value;
}

char Piece::getColor()
{
    if (value == 0)
        return 'u';
    return value > 0 ? 'w' : 'b';
}

void Piece::setInfo(char name, int value)
{
    this->name = name;
    this->value = value;
}

bool Piece::isSameColor(Piece piece)
{
    return value * piece.value > 0;
}

Pawn::Pawn(int value) : Piece('P', value)
{
    moveCount = 0;
}

Knight::Knight(int value) : Piece('N', value)
{
}

Bishop::Bishop(int value) : Piece('B', value)
{
}

Rook::Rook(int value) : Piece('R', value)
{
    isMoved = false;
}

bool Rook::getIsMoved()
{
    return isMoved;
}

void Rook::setMoved(bool isMoved)
{
    this->isMoved = isMoved;
}

Queen::Queen(int value) : Piece('Q', value)
{
}

King::King(int value) : Piece('K', value)
{
    isMoved = false;
}

bool King::getIsMoved()
{
    return isMoved;
}
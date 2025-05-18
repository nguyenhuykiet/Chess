#include "pieces.h"

#include <utility>

#define rank first
#define file second

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

void Piece::setInfo(char name, int value)
{
    this->name = name;
    this->value = value;
}

Pawn::Pawn(int value) : Piece('P', value)
{
    step.rank = (value > 0) ? 1 : -1;
    step.file = 1;
}

Knight::Knight(int value) : Piece('N', value)
{
    step = {2, 2};
}

Bishop::Bishop(int value) : Piece('B', value)
{
    step = {8, 8};
}

Rook::Rook(int value) : Piece('R', value)
{
    isMoved = false;
    step = {8, 8};
}

bool Rook::getIsMoved()
{
    return isMoved;
}

Queen::Queen(int value) : Piece('Q', value)
{
    step = {8, 8};
}

King::King(int value) : Piece('K', value)
{
    isMoved = false;
    step = {1, 1};
}

bool King::getIsMoved()
{
    return isMoved;
}
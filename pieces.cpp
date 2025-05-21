#include "pieces.h"

#include <stdlib.h>
#include <vector>
#include <utility>

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

vector<pair<int, int>> Piece::getDirections()
{
    return directions;
}

pair<int, int> Piece::getRange()
{
    return range;
}

Pawn::Pawn(int value) : Piece('P', value)
{
    directions.push_back({value / abs(value), 0});
    range = {1, 1};
}

Knight::Knight(int value) : Piece('N', value)
{
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2)
            for (int rankStep = 1; rankStep <= 2; ++rankStep)
            {
                int fileStep = 3 - rankStep;
                directions.push_back({i * rankStep, j * fileStep});
            }

    range = {1, 1};
}

Bishop::Bishop(int value) : Piece('B', value)
{
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2)
            directions.push_back({i, j});

    range = {1, 7};
}

Rook::Rook(int value) : Piece('R', value)
{
    isMoved = false;

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i * j == 0)
                directions.push_back({i, j});

    range = {1, 7};
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
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (abs(i) + abs(j) == 1)
                directions.push_back({i, j});

    range = {1, 7};
}

King::King(int value) : Piece('K', value)
{
    isMoved = false;

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (abs(i) + abs(j) == 1)
                directions.push_back({i, j});

    range = {1, 1};
}

bool King::getIsMoved()
{
    return isMoved;
}
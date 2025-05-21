#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include <vector>
#include <utility>

using namespace std;

class Piece
{
protected:
    char name;
    int value;
    vector<pair<int, int>> directions;
    pair<int, int> range;

public:
    Piece();
    Piece(char name, int value);
    bool operator==(Piece piece);
    char getName();
    int getValue();
    char getColor();
    void setInfo(char name, int value);
    bool isSameColor(Piece piece);
    vector<pair<int, int>> getDirections();
    pair<int, int> getRange();
};

class Pawn : public Piece
{
public:
    Pawn(int value);
};

class Knight : public Piece
{
public:
    Knight(int value);
};

class Bishop : public Piece
{
public:
    Bishop(int value);
};

class Rook : public Piece
{
private:
    bool isMoved;

public:
    Rook(int value);
    bool getIsMoved();
    void setMoved(bool isMoved);
};

class Queen : public Piece
{
public:
    Queen(int value);
};

class King : public Piece
{
private:
    bool isMoved;

public:
    King(int value);
    bool getIsMoved();
};

#endif
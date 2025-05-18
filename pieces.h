#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include <utility>

using namespace std;

class Piece
{
protected:
    char name;
    int value;
    pair<int, int> step;

public:
    Piece();
    Piece(char name, int value);
    bool operator==(Piece piece);
    char getName();
    int getValue();
    void setInfo(char name, int value);
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
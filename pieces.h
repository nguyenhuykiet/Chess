#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

using namespace std;

class Piece
{
protected:
    char name;
    int value;

public:
    Piece();
    Piece(char name, int value);
    bool operator==(Piece piece);
    char getName();
    int getValue();
    char getColor();
    void setInfo(char name, int value);
    bool isSameColor(Piece piece);
};

class Pawn : public Piece
{
private:
    int moveCount;

public:
    Pawn(int value);
    void getEnPassant();
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
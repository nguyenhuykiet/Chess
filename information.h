#ifndef INFORMATION_H_INCLUDED
#define INFORMATION_H_INCLUDED

#include "pieces.h"
#include <string>
#include <vector>

using namespace std;

class Move
{
private:
    pair<int, int> startPosition;
    pair<int, int> step;
    Piece promotedPiece;

public:
    Move(pair<int, int> startPosition, pair<int, int> step, Piece promotedPiece = Piece('U', 0));
    Move(string moveStr);
    string getMoveStr();
    pair<int, int> getStartPosition();
    pair<int, int> getStep();
    Piece getPromotedPiece();
};

class Board
{
private:
    Piece board[8][8];

public:
    Board();
    Piece getPiece(pair<int, int> position);
    int getPoint();
    void makeMove(Move move);
    bool isCheck(pair<int, int> position);
    bool isLegalMove(Move move);
    vector<Move> getLegalMoves(char color);
};

#endif
#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "move.h"

#include <utility>
#include <vector>

using namespace std;

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
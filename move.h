#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "pieces.h"

#include <string>
#include <utility>

using namespace std;

class Move
{
private:
    pair<int, int> startPosition;
    pair<int, int> step;
    /**
     * 5 types of move
     * 'n': normal move
     * 'c': King side castling
     * 'C': Queen side castling
     * 'p': first 2-step move of Pawn
     * 'e': en passant
     * 'k'/'b'/'r'/'q': promote to Knight/Bishop/Rook/Queen
     */
    char moveType;

public:
    Move(pair<int, int> startPosition, pair<int, int> step, char moveType);
    Move(string moveStr);
    string getMoveStr();
    pair<int, int> getStartPosition();
    pair<int, int> getStep();
};

#endif
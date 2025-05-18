#include "information.h"
#include "calculation.h"

#include <utility>

#define rank first
#define file second

using namespace std;

Move::Move(pair<int, int> startPosition, pair<int, int> step, Piece promotedPiece)
{
    this->startPosition = startPosition;
    this->step = step;
    this->promotedPiece = promotedPiece;
}

Move::Move(string moveStr)
{
    pair<int, int> startPosition = {moveStr[0] - 'a', moveStr[1] - '0'};
    pair<int, int> step = {moveStr[2] - moveStr[0], moveStr[3] - moveStr[1]};
}

string Move::getMoveStr()
{
    string moveStr = "";
    pair<int, int> targetPosition = {startPosition.rank + step.rank, startPosition.file + step.file};

    moveStr += char(startPosition.file + 'a');
    moveStr += char(startPosition.rank + '1');
    moveStr += char(targetPosition.file + 'a');
    moveStr += char(targetPosition.rank + '1');

    return moveStr;
}

pair<int, int> Move::getStartPosition()
{
    return startPosition;
}

pair<int, int> Move::getStep()
{
    return step;
}

Piece Move::getPromotedPiece()
{
    return promotedPiece;
}

Board::Board()
{
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
            board[rank][file] = Piece('u', 0);

    for (int file = 0; file < 7; ++file)
    {
        board[1][file] = Pawn(1);
        board[6][file] = Pawn(-1);
    }

    board[0][0] = Rook(5);
    board[0][7] = Rook(5);
    board[0][1] = Knight(3);
    board[0][6] = Knight(3);
    board[0][2] = Bishop(3);
    board[0][5] = Bishop(3);
    board[0][3] = Queen(9);
    board[0][4] = King(90);

    board[7][0] = Rook(-5);
    board[7][7] = Rook(-5);
    board[7][1] = Knight(-3);
    board[7][6] = Knight(-3);
    board[7][2] = Bishop(-3);
    board[7][5] = Bishop(-3);
    board[7][3] = Queen(-9);
    board[7][4] = King(-90);
}

Piece Board::getPiece(pair<int, int> position)
{
    return board[position.rank][position.file];
}

int Board::getPoint()
{
    int point = 0;
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
            point += board[rank][file].getValue();
    return point;
}

void Board::makeMove(Move move)
{
    pair<int, int> startPosition = move.getStartPosition();
    pair<int, int> step = move.getStep();
    pair<int, int> targetPosition = {startPosition.rank + step.rank, startPosition.file + step.file};
    swap(board[startPosition.rank][startPosition.file], board[targetPosition.rank][targetPosition.file]);
    board[targetPosition.rank][targetPosition.file].setInfo('U', 0);
}

bool Board::isCheck()
{
    //
    return false;
}

bool Board::isCheckMate()
{
    //
    return false;
}
#include "information.h"
#include "calculation.h"

#include <utility>
#include <vector>

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

    for (int file = 0; file < 8; ++file)
    {
        board[1][file] = Pawn(1);
        board[6][file] = Pawn(-1);
    }

    board[0][0] = Rook(5);              board[7][0] = Rook(-5);
    board[0][1] = Knight(3);            board[7][1] = Knight(-3);
    board[0][2] = Bishop(3);            board[7][2] = Bishop(-3);
    board[0][3] = Queen(9);             board[7][3] = Queen(-9);
    board[0][4] = King(90);             board[7][4] = King(-90);
    board[0][5] = Bishop(3);            board[7][5] = Bishop(-3);
    board[0][6] = Knight(3);            board[7][6] = Knight(-3);
    board[0][7] = Rook(5);              board[7][7] = Rook(-5);
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

bool Board::isCheck(pair<int, int> position)
{
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
            if (!board[position.rank][position.file].isSameColor(board[rank][file]))
            {
                char name = board[rank][file].getName();

                if (name == 'U')
                    continue;

                vector<pair<int, int>> directions = board[rank][file].getDirections();
                pair<int, int> range = board[rank][file].getRange();

                // Pawn / Knight / King
                if (name == 'P' || name == 'N' || name == 'K')
                {
                    for (int i = 0; i < directions.size(); ++i)
                        for (int base = range.first; base <= range.second; ++base)
                            if (make_pair(rank + base * directions[i].rank, file + base * directions[i].file) == position)
                                return true;
                }

                // Bishop / Rook / Queen
                else if (rank == position.rank ||
                         file == position.file ||
                         rank + file == position.rank + position.file ||
                         rank - file == position.rank - position.file)
                {
                    pair<int, int> direction;
                    direction.rank = (file == position.file) ? 0 : -(rank - position.rank) / abs(rank - position.rank);
                    direction.file = (rank == position.rank) ? 0 : -(file - position.file) / abs(file - position.file);
                    pair<int, int> buffer = {rank + direction.rank, file + direction.file};
                    bool flag = false;
                    while (buffer != position)
                    {
                        if (board[buffer.rank][buffer.file].getName() != 'U')
                        {
                            flag = true;
                            break;
                        }
                        buffer.rank += direction.rank;
                        buffer.file += direction.file;
                    }
                    if (!flag)
                        return true;
                }
            }
    return false;
}

bool Board::isLegalMove(Move move)
{
    pair<int, int> startPosition = move.getStartPosition();
    pair<int, int> step = move.getStep();
    pair<int, int> targetPosition = {startPosition.rank + step.rank, startPosition.file + step.file};

    if (targetPosition.rank < 0 || targetPosition.rank > 7 ||
        targetPosition.file < 0 || targetPosition.file > 7)
        return false;

    if (board[startPosition.rank][startPosition.file].isSameColor(board[targetPosition.rank][targetPosition.file]))
        return false;

    Board newBoard;
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
            newBoard.board[rank][file] = board[rank][file];

    newBoard.makeMove(move);
    Piece movedPiece = newBoard.board[startPosition.rank][startPosition.file];
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
        {
            Piece piece = newBoard.board[rank][file];
            if (piece.getName() == 'K' && piece.isSameColor(movedPiece))
                return !isCheck({rank, file});
        }
    return true;
}

vector<Move> Board::getLegalMoves(char color)
{
    vector<Move> legalMoves;
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
            if (board[rank][file].getColor() == color)
            {
                // Normal move
                vector<pair<int, int>> directions = board[rank][file].getDirections();
                pair<int, int> range = board[rank][file].getRange();
                for (int i = 0; i < directions.size(); ++i)
                    for (int base = range.first; base <= range.second; ++base)
                    {
                        Move move = Move({rank, file}, {base * directions[i].rank, base * directions[i].file});
                        if (isLegalMove(move))
                            legalMoves.push_back(move);
                        else
                            break;
                    }

                // Special move
            }
    return legalMoves;
}
#include "board.h"

#define rank first
#define file second

using namespace std;

Board::Board()
{
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
            board[rank][file] = Piece('U', 0);

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

    // Normal move

    // Castling

    // Special move of Pawn

    // First 2-step

    // En passant

    // Promotion
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
                        Move move = Move({rank, file}, {base * directions[i].rank, base * directions[i].file}, 'n');
                        if (isLegalMove(move))
                            legalMoves.push_back(move);
                        else
                            break;
                    }

                char name = board[rank][file].getName();

                // Castling
                if (name == 'K' && !static_cast<King *>(&board[rank][file])->getIsMoved() && !isCheck({0, 4}))
                {
                    int curRank = (color == 'w') ? 0 : 7;

                    // King side
                    if (board[curRank][7].getName() == 'R' && !static_cast<Rook *>(&board[curRank][7])->getIsMoved() &&
                        board[curRank][5].getName() == 'U' && board[curRank][6].getName() == 'U' &&
                        !isCheck({curRank, 5}) && !isCheck({curRank, 6}))
                        legalMoves.push_back(Move({0, 4}, {0, 0}, 'c'));

                    // Queen side
                    if (board[curRank][0].getName() == 'R' && !static_cast<Rook *>(&board[curRank][0])->getIsMoved() &&
                        board[curRank][1].getName() == 'U' && board[curRank][2].getName() == 'U' && board[curRank][3].getName() == 'U' &&
                        !isCheck({curRank, 2}) && !isCheck({curRank, 3}))
                        legalMoves.push_back(Move({0, 4}, {0, 0}, 'C'));
                }

                // Special move of Pawn
                if (name == 'P')
                {
                    // First 2-step move
                    if ((rank == 1 && board[1][file].getColor() == 'w' && board[3][file].getName() == 'U') ||
                        rank == 6 && board[6][file].getColor() == 'b' && board[4][file].getName() == 'U')
                    {
                        int direction = (board[rank][file].getColor() == 'w') ? 1 : -1;
                        legalMoves.push_back(Move({rank, file}, {rank + 3 * direction, file}, 'p'));
                    }

                    // En passant
                    for (int i = -1; i <= 1; i += 2)
                        if (file + i >= 0 && file + i < 8 &&
                            board[rank][file + 1].getName() == 'P' &&
                            board[rank][file + i].getColor() != color &&
                            static_cast<Pawn *>(&board[rank][file + i])->getEnPassant())
                            legalMoves.push_back(Move({rank, file}, {board[rank][file].getValue(), 1}, 'e'));

                    // Promotion
                    {
                        int direction = board[rank][file].getValue();
                        if (board[rank + direction][file].getName() == 'U')
                        {
                            pair<int, int> startPosition = {rank, file};
                            pair<int, int> step = {direction, 0};

                            legalMoves.push_back(Move({startPosition, step, 'k'}));
                            legalMoves.push_back(Move({startPosition, step, 'b'}));
                            legalMoves.push_back(Move({startPosition, step, 'r'}));
                            legalMoves.push_back(Move({startPosition, step, 'q'}));
                        }
                    }
                }
            }
    return legalMoves;
}
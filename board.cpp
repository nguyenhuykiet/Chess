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

    whiteKingPosition = {0, 4};
    blackKingPosition = {7, 4};
    turn = 'w';
    enPassantPosition = {8, 8};
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
    char typeOfMove = move.getTypeOfMove();

    // Normal move
    if (typeOfMove == 'n')
    {
        swap(board[startPosition.rank][startPosition.file], board[targetPosition.rank][targetPosition.file]);
        board[targetPosition.rank][targetPosition.file].setInfo('U', 0);
    }

    // King side castling
    if (typeOfMove == 'c')
    {
        int curRank = startPosition.rank;
        swap(board[curRank][4], board[curRank][6]);
        swap(board[curRank][7], board[curRank][5]);
    }

    // Queen side castling
    if (typeOfMove == 'C')
    {
        int curRank = startPosition.rank;
        swap(board[curRank][4], board[curRank][2]);
        swap(board[curRank][0], board[curRank][3]);
    }

    // En passant
    if (typeOfMove == 'e')
    {
        swap(board[startPosition.rank][startPosition.file], board[targetPosition.rank][targetPosition.file]);
        board[enPassantPosition.rank][enPassantPosition.file].setInfo('U', 0);
    }

    // Promotion
    if (typeOfMove == 'N' || typeOfMove == 'B' || typeOfMove == 'R' || typeOfMove == 'Q')
    {
        board[startPosition.rank][startPosition.file].setInfo('U', 0);
        int sign = board[startPosition.rank][startPosition.file].getValue();
        switch (typeOfMove)
        {
        case 'N':
            board[startPosition.rank][startPosition.file] = Knight(3 * sign);
            break;

        case 'B':
            board[startPosition.rank][startPosition.file] = Bishop(3 * sign);
            break;

        case 'R':
            board[startPosition.rank][startPosition.file] = Rook(5 * sign);
            break;

        case 'Q':
            board[startPosition.rank][startPosition.file] = Queen(9 * sign);
            break;
        }
    }

    // Cancel en passant
    enPassantPosition = {8, 8};

    // First 2-step
    if (typeOfMove == 'p')
    {
        swap(board[startPosition.rank][startPosition.file], board[targetPosition.rank][targetPosition.file]);
        enPassantPosition = startPosition;
    }
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

vector<Move> Board::getLegalMoves()
{
    legalMoves.clear();
    for (int rank = 0; rank < 8; ++rank)
        for (int file = 0; file < 8; ++file)
            if (board[rank][file].getColor() == turn)
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
                    // King side
                    if (board[rank][7].getName() == 'R' && !static_cast<Rook *>(&board[rank][7])->getIsMoved() &&
                        board[rank][5].getName() == 'U' && board[rank][6].getName() == 'U' &&
                        !isCheck({rank, 5}) && !isCheck({rank, 6}))
                        legalMoves.push_back(Move({rank, 4}, {0, 2}, 'c'));

                    // Queen side
                    if (board[rank][0].getName() == 'R' && !static_cast<Rook *>(&board[rank][0])->getIsMoved() &&
                        board[rank][1].getName() == 'U' && board[rank][2].getName() == 'U' && board[rank][3].getName() == 'U' &&
                        !isCheck({rank, 2}) && !isCheck({rank, 3}))
                        legalMoves.push_back(Move({rank, 4}, {0, 2}, 'C'));
                }

                // Special move of Pawn
                if (name == 'P')
                {
                    int direction = (turn == 'w') ? 1 : -1;

                    // First 2-step move
                    if ((rank == 1 || rank == 6) && board[rank + 2 * direction][file].getName() == 'U')
                        legalMoves.push_back(Move({rank, file}, {2 * direction, 0}, 'p'));

                    // En passant
                    for (int i = -1; i <= 1; i += 2)
                        if (file + i >= 0 && file + i < 8 &&
                            board[rank][file + 1].getName() == 'P' &&
                            board[rank][file + i].getColor() != turn &&
                            make_pair(rank, file + i) == enPassantPosition)
                            legalMoves.push_back(Move({rank, file}, {direction, 1}, 'e'));

                    // Promotion
                    if (rank == 6 && board[rank + direction][file].getName() == 'U')
                    {
                        pair<int, int> startPosition = {rank, file};
                        pair<int, int> step = {direction, 0};

                        legalMoves.push_back(Move({startPosition, step, 'N'}));
                        legalMoves.push_back(Move({startPosition, step, 'B'}));
                        legalMoves.push_back(Move({startPosition, step, 'R'}));
                        legalMoves.push_back(Move({startPosition, step, 'Q'}));
                    }
                }
            }
    return legalMoves;
}

bool Board::endGame()
{
    if (!legalMoves.empty())
        return false;

    if (turn == 'w' && isCheck(whiteKingPosition))
        return true;

    if (turn == 'b' && isCheck(blackKingPosition))
        return true;

    return false;
}
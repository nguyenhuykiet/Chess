#include "move.h"

#include <utility>

#define rank first
#define file second

using namespace std;

Move::Move(pair<int, int> startPosition, pair<int, int> step, char moveType)
{
    this->startPosition = startPosition;
    this->step = step;
    this->moveType = moveType;
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
#include <iostream>
#include "information.h"

using namespace std;

int main()
{
    Move move = Move({0, 1}, {2, 1});
    cout << move.getMoveStr();
}
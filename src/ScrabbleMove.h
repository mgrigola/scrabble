#ifndef SCRABBLEMOVE_H
#define SCRABBLEMOVE_H

#include "ScrabbleTile.h"
#include "ScrabbleBoard.h"
#include "ScrabbleHand.h"

//the class to find the best move, check if things are legal, the score, etc?

//can we use a heap to store the best moves?


class TilePositionPair
{
public:
    TilePositionPair(ScrabbleTile* _pTile, size_t _row, size_t _col) : pTile(_pTile), row(_row), col(_col) {}
    ScrabbleTile* pTile;
    size_t row, col;
};

class ScrabbleMove
{
private:

public:
    ScrabbleMove();    

};

#endif // SCRABBLEMOVE_H

#ifndef TILEBAGENUS_H
#define TILEBAGENUS_H

#include "TileBag.h"

class TileBagEnUS : public TileBag
{
private:
    unsigned int tileMaxCounts[27];
    unsigned int tileCounts[27];
    unsigned int tileValues[27];

public:
    TileBagEnUS();
};

#endif // TILEBAGENUS_H

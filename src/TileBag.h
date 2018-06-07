#ifndef TILEBAG_H
#define TILEBAG_H

#include "ScrabbleTile.h"
#include <vector>
#include <string>
#include <fstream>

//#include <stdlib.h>
#include <time.h>

class TileBag
{
private:
    unsigned int alphabetLength;
    unsigned int remainingTileCount;
    unsigned int maxTileCount;
    std::vector<ScrabbleTile> tilesInBag;

    unsigned int balanced_random(unsigned int maxRandomRange);

public:
    //derived constructor must set alphabetLength/totalTileCount & fill tilesInBag with totalTileCount tiles
    TileBag(const std::string& fileTileLoad="");
    bool load_tile_bag_file(const std::string& fileTileLoad);
    //virtual ~TileBag() {}  //if using destrcutor, make virtual if want derived class to call
    void shuffle_bag(void);
    bool draw_tile(ScrabbleTile& drawnTile);
    void exchange_tiles(std::vector<ScrabbleTile>& unwantedTiles);
    bool is_empty(void);
};

#endif // TILEBAG_H

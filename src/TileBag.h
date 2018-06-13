#ifndef TILEBAG_H
#define TILEBAG_H

#include "ScrabbleTile.h"
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

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
    std::unordered_map<char, uint16_t> tileVals, tileCounts;  //hash table

    //derived constructor must set alphabetLength/totalTileCount & fill tilesInBag with totalTileCount tiles
    TileBag(const std::string& fileTileLoad="");
    bool load_tile_bag_file(const std::string& fileTileLoad);
    //virtual ~TileBag() {}  //if using destrcutor, make virtual if want derived class to call
    void shuffle_bag(void);
    ScrabbleTile* draw_tile(void);
    void exchange_tiles(std::vector<ScrabbleTile*>& unwantedTiles);
    bool is_empty(void);

    void decrement_tile_count(char cLetter)  { --tileCounts[cLetter]; }
    void increment_tile_count(char cLetter)  { ++tileCounts[cLetter]; }

    uint16_t get_letter_val(char cLetter)  { return tileVals.count(cLetter) ? tileVals[cLetter] : 0; }
    uint16_t get_letter_count(char cLetter)  { return tileCounts.count(cLetter) ? tileCounts[cLetter] : 0; }
};

#endif // TILEBAG_H

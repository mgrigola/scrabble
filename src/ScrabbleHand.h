#ifndef SCRABBLEHAND_H
#define SCRABBLEHAND_H

#include "ScrabbleTile.h"
#include "TileBag.h"

#include <vector>
#include <string>

class ScrabbleHand
{
private:
    unsigned int tileCount;
    unsigned int maxTileCount;

    std::vector<ScrabbleTile> tilesInHand;
    bool remove_from_hand(std::vector<unsigned int>tilesToRemoveIndices);

public:
    ScrabbleHand(unsigned int maxTiles);
    bool draw_to_fill(TileBag& srcBag);
    bool exchange_tiles(TileBag& srcBag, std::vector<unsigned int>tilesToExchangeIndices);
    void get_letters(std::string& letterString);
    bool is_empty(void);
};

#endif // SCRABBLEHAND_H

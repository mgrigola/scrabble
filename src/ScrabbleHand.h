#ifndef SCRABBLEHAND_H
#define SCRABBLEHAND_H

#include "ScrabbleTile.h"
#include "TileBag.h"

#include <vector>
#include <string>
#include <iostream>

class ScrabbleHand
{
private:
    unsigned int tileCount;
    unsigned int maxTileCount;

    bool remove_indices_from_hand(std::vector<unsigned int>tilesToRemoveIndices);

public:
    std::vector<ScrabbleTile*> tilesInHand;

    ScrabbleHand(unsigned int maxTiles);
    bool draw_to_fill(TileBag& srcBag);
    bool exchange_tiles(TileBag& srcBag, std::vector<unsigned int>tilesToExchangeIndices);
    void get_letters(std::string& letterString) const;
    bool is_empty(void);
    friend std::ostream& operator<<(std::ostream& stream, const ScrabbleHand& hand);

    bool remove_from_hand(ScrabbleTile* pTileToRemove);
};

#endif // SCRABBLEHAND_H

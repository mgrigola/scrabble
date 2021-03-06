#include "ScrabbleHand.h"

ScrabbleHand::ScrabbleHand(unsigned int maxTiles) :
    maxTileCount(maxTiles),
    tileCount(0)
{
    tilesInHand = std::vector<ScrabbleTile*>(maxTileCount, nullptr);
}

bool ScrabbleHand::draw_to_fill(TileBag& srcBag)
{
    while(tileCount<maxTileCount)
    {
        ScrabbleTile* pTile = srcBag.draw_tile();
        //if bag ran out of tiles, it returns false and we can't draw any more tiles
        if ( pTile == nullptr )
            return false;
        tilesInHand[tileCount] = pTile;
        ++tileCount;
    }
    return true;
}


//this should get called after like playing some tiles (they remove from hand and go to board)
//assume tileToRemoveIndices is sorted
bool ScrabbleHand::remove_indices_from_hand(std::vector<unsigned int> removeIndices)
{
    size_t newIdx = 0, rmvElemNo = 0, rmvCount = removeIndices.size();
    //we want to remove each element of our hand specified in removeIndices and shift all the remaining stuff down
    //we can be more efficient than shifting everything down 1 for each removed tile (see below!) but result is same
    //everything after new tileCount we be overwritten next time we draw or just ignored if game almost over
    for (size_t oldIdx=0; oldIdx<tileCount; ++oldIdx)
    {
        //if tile is removed, we just step over it (and move to the next tile to be removed) we may replace it later
        //check if rmvIdx > length(removeIndices) before trying to read element (after reach end of remove list, everything else just shifts into place)
        if (rmvElemNo<rmvCount && removeIndices[rmvElemNo] == oldIdx)
            ++rmvElemNo;

        //else we keep this tile. if we removed tiles already, then we shift this tile up to its correct position
        else
        {
            //if we haven't removed tiles yet, this tile doesn't need to move
            if (newIdx != oldIdx)
                tilesInHand[newIdx] = tilesInHand[oldIdx];

            ++newIdx; //newPos keeps track of our position in the new hand (counts how many tiles we've kept so far)
        }
    }

    bool removedAllRequested = (tileCount <= removeIndices[rmvCount-1]);

    tileCount = newIdx;
    return removedAllRequested;   //this could fail if we try to remove tiles that aren't in our hand (tileCount was already < rmvIdx, like 3 tiles left and request to remove tile #4 - not possible)
}


//
bool ScrabbleHand::exchange_tiles(TileBag &srcBag, std::vector<unsigned int> tilesToExchangeIndices)
{
    //can't exchange when bag is empty
    if (srcBag.is_empty())
        return false;

    //gather the unwanted tiles from hand
    std::vector<ScrabbleTile*> swapTiles(tilesToExchangeIndices.size());
    size_t swapIdx = 0;
    for (unsigned int exchangeIdx : tilesToExchangeIndices)
        swapTiles[swapIdx++] = tilesInHand[exchangeIdx];

    //put unwanted tiles back in bag and draw equal number of new tiles (new tiles now in swapTiles)
    srcBag.exchange_tiles(swapTiles);

    //put new tiles back into hand in same positions as old tiles
    for (size_t swapIdx=0; swapIdx<swapTiles.size(); ++swapIdx)
    {
        unsigned int exchangeIdx = tilesToExchangeIndices[swapIdx];
        tilesInHand[exchangeIdx] = swapTiles[swapIdx];
    }
    return true;
}

//pretty inefficient, not very elegant... maybe there's a better way to do this? maybe hash table index to map tile to position in tilesInHand? maybe tilesInHand should be linked list? maybe getstuff built as is and worry about cleanup at end...
bool ScrabbleHand::remove_from_hand(ScrabbleTile* pTileToRemove)
{
    for (size_t tileNo=0; tileNo<tileCount; ++tileNo)           //loop over tiles in hand
    {
        if (tilesInHand[tileNo] == pTileToRemove)              //if found tile we're looking to remove
        {
            --tileCount;                                        //we want tiles[0:tileCount-1] to be our hand
            if (tileNo != tileCount)                            //we ditch the tile we found
                tilesInHand[tileNo] = tilesInHand[tileCount];   //so 'swap' with tilesInHand[tileCount], shift last element into our now-smaller hand
            return true;                                        //stop loop once found
        }
    }
    return false; //didn't find the requested tile to remove. didn't remove anything
}


void ScrabbleHand::get_letters(std::string& letterString) const
{
    letterString.reserve(tileCount);
    //loop on tileNo, not items in tilesInHand. we could have fewer than 7 tiles, but hand length is always 7
    for (size_t tileNo=0; tileNo < tileCount; ++tileNo)
        letterString.push_back( tilesInHand[tileNo]->tileLetter );
}


bool ScrabbleHand::is_empty(void)
{
    return (tileCount == 0);
}

std::ostream& operator<<(std::ostream& stream, const ScrabbleHand& hand)
{
    std::string letters;
    hand.get_letters(letters);
    stream << letters;
    return stream;
}

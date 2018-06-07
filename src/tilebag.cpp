#include "TileBag.h"

TileBag::TileBag(const std::string& fileTileLoad) :
    alphabetLength(0),
    remainingTileCount(0),
    maxTileCount(0)
{
    //allow passing load file in constructor or calling load_tile_bag_file separately
    if ( !fileTileLoad.empty() )
        load_tile_bag_file(fileTileLoad);
}

//lnTxt=<bagChar>    <bagCount>  <tileValue>
//returns false if we're missing any piece of the required info
bool parse_bag_line(const std::string& lnTxt, char& bagChar, unsigned int& bagCount, unsigned int& tileValue)
{
    if ( lnTxt.empty() )  return false;
    size_t lastPos=0, delimPos;

    //letter
    delimPos = lnTxt.find("\t", lastPos);
    if (delimPos == std::string::npos)  return false;
    bagChar = lnTxt.substr(lastPos,delimPos)[0];
    lastPos = delimPos+1;

    //count
    delimPos = lnTxt.find("\t", lastPos);
    if (delimPos == std::string::npos)  return false;
    bagCount = atoi( lnTxt.substr(lastPos,delimPos).c_str() );
    lastPos = delimPos+1;

    //point value
    delimPos = lnTxt.size();
    if (delimPos == lastPos)  return false;
    tileValue = atoi( lnTxt.substr(lastPos,delimPos).c_str() );

    return true;
}


//possibly support different languages or variations in tile value or rarity with customizations to tile file
//see existing files for format example. Letters should be all caps or match dictionary/wordlist format
bool TileBag::load_tile_bag_file(const std::string& fileTileLoad)
{
    std::ifstream inputFile( fileTileLoad );
    if (!inputFile.is_open())
        return false;

    maxTileCount = 0;
    char bagChar;
    unsigned int bagCount, tileValue;
    std::string lnTxt;

    //each row is letter<tab>count<tab>value. blanks are "?". empty rows are okay i guess
    while (std::getline(inputFile, lnTxt, '\n'))
    {
        if ( parse_bag_line(lnTxt, bagChar, bagCount, tileValue) )
        {
            //add a scrabbletile for each copy of tile/letter in the bag
            for (size_t letterNo=0; letterNo<bagCount; ++letterNo)
                tilesInBag.push_back( ScrabbleTile(bagChar, tileValue, maxTileCount+letterNo) );

            ++alphabetLength;
            maxTileCount += bagCount;
        }
    }

    inputFile.close();
    remainingTileCount = maxTileCount;
    shuffle_bag();
    return (maxTileCount>0);  //return true (success) if we have some letters in the bag
}

//my own implementation for fun. return uniform distrib int in range [0,maxRandomRange]  (inclusive)
unsigned int TileBag::balanced_random(unsigned int maxRandomRange)
{
    //higher rand() than maxValid (on mod/%) wraps around to 0 but doesn't reach maxRandomRange (on mod/%) at RAND_MAX,
    //so above maxValid is biased toward lower output. Simple solution: discard values above maxValid and roll again
    unsigned int maxValid = RAND_MAX - (RAND_MAX+1)%(maxRandomRange+1);
    unsigned int rawRand = rand();
    while (rawRand > maxValid)
        rawRand = rand();

    return rawRand%(maxRandomRange+1);
}


//perform fisher-yates shuffle of the tiles
//can be thought of as repeatedly choosing the next tile in the bag from/amongst unchosen tiles
void TileBag::shuffle_bag(void)
{
    srand(time(NULL));  //seed random number generator
    for (size_t sortedPartStart=remainingTileCount-1; sortedPartStart>0; --sortedPartStart)
    {
        unsigned int swapPos = balanced_random(sortedPartStart);
        if (swapPos != sortedPartStart)
            std::swap(tilesInBag[swapPos], tilesInBag[sortedPartStart]);
    }
}


//simply take the top tile from the deck/bag. We do not pop/delete the element, just decrement remainingCount
//while in hand or in play, the tile remains in its place in the tileBag vector
//returns false if out of tiles to draw, else true
bool TileBag::draw_tile(ScrabbleTile& drawnTile)
{
    if (remainingTileCount > 0)
    {
        --remainingTileCount;
        drawnTile = tilesInBag[remainingTileCount];
        return true;
    }
    return false;
}


//we put the unwanted tiles 'back in the bag' first, then draw the new hand - possibly giving the same unwanted tiles
//note: we lose the original configuration of the bag upon shuffling (and we have no memory of what tiels players exchanged)
void TileBag::exchange_tiles(std::vector<ScrabbleTile>& unwantedTiles)
{
    //put unwanted tiles back in bag
    for (ScrabbleTile sTile : unwantedTiles)
    {
        tilesInBag[remainingTileCount] = sTile;
        ++remainingTileCount;
    }

    //reshuffle remaining tiles (remainingTiles+1 to maxTileCount are untouched, maintain draw order)
    shuffle_bag();

    //draw new tiles from top.
    for (size_t replaceTileNo=0; replaceTileNo<unwantedTiles.size(); ++replaceTileNo)
    {
        unwantedTiles[replaceTileNo] = tilesInBag[remainingTileCount];
        --remainingTileCount;
    }
}


bool TileBag::is_empty(void)
{
    return (remainingTileCount == 0);
}

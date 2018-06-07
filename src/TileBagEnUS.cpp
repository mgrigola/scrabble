#include "TileBagEnUS.h"

TileBagEnUS::TileBagEnUS()
{
    alphabetLength = 27;  // one might want to implement other language i suppose

    tileMaxCounts[ 0] =  9;  // A
    tileMaxCounts[ 1] =  2;  // B
    tileMaxCounts[ 2] =  2;  // C
    tileMaxCounts[ 3] =  4;  // D
    tileMaxCounts[ 4] = 12;  // E
    tileMaxCounts[ 5] =  2;  // F
    tileMaxCounts[ 6] =  3;  // G
    tileMaxCounts[ 7] =  2;  // H
    tileMaxCounts[ 8] =  9;  // I
    tileMaxCounts[ 9] =  1;  // J
    tileMaxCounts[10] =  1;  // K
    tileMaxCounts[11] =  4;  // L
    tileMaxCounts[12] =  2;  // M
    tileMaxCounts[13] =  6;  // N
    tileMaxCounts[14] =  8;  // O
    tileMaxCounts[15] =  2;  // P
    tileMaxCounts[16] =  1;  // Q
    tileMaxCounts[17] =  6;  // R
    tileMaxCounts[18] =  4;  // S
    tileMaxCounts[19] =  6;  // T
    tileMaxCounts[20] =  4;  // U
    tileMaxCounts[21] =  2;  // V
    tileMaxCounts[22] =  2;  // W
    tileMaxCounts[23] =  1;  // X
    tileMaxCounts[24] =  2;  // Y
    tileMaxCounts[25] =  1;  // Z
    tileMaxCounts[26] =  2;  // ?  (blanks)

    tileValues[ 0] =  1;  // A
    tileValues[ 1] =  3;  // B
    tileValues[ 2] =  3;  // C
    tileValues[ 3] =  2;  // D
    tileValues[ 4] =  1;  // E
    tileValues[ 5] =  4;  // F
    tileValues[ 6] =  2;  // G
    tileValues[ 7] =  4;  // H
    tileValues[ 8] =  1;  // I
    tileValues[ 9] =  8;  // J
    tileValues[10] =  5;  // K
    tileValues[11] =  1;  // L
    tileValues[12] =  3;  // M
    tileValues[13] =  1;  // N
    tileValues[14] =  1;  // O
    tileValues[15] =  3;  // P
    tileValues[16] = 10;  // Q
    tileValues[17] =  1;  // R
    tileValues[18] =  1;  // S
    tileValues[19] =  1;  // T
    tileValues[20] =  1;  // U
    tileValues[21] =  4;  // V
    tileValues[22] =  4;  // W
    tileValues[23] =  8;  // X
    tileValues[24] =  4;  // Y
    tileValues[25] = 10;  // Z
    tileValues[26] =  0;

    char tileChars[27];
    tileChars[ 0] = "A";
    tileChars[ 1] = "B";
    tileChars[ 2] = "C";
    tileChars[ 3] = "D";
    tileChars[ 4] = "E";
    tileChars[ 5] = "F";
    tileChars[ 6] = "G";
    tileChars[ 7] = "H";
    tileChars[ 8] = "I";
    tileChars[ 9] = "J";
    tileChars[10] = "K";
    tileChars[11] = "L";
    tileChars[12] = "M";
    tileChars[13] = "N";
    tileChars[14] = "O";
    tileChars[15] = "P";
    tileChars[16] = "Q";
    tileChars[17] = "R";
    tileChars[18] = "S";
    tileChars[19] = "T";
    tileChars[20] = "U";
    tileChars[21] = "V";
    tileChars[22] = "W";
    tileChars[23] = "X";
    tileChars[24] = "Y";
    tileChars[25] = "Z";
    tileChars[26] = "?";

    remainingTileCount = 0;
    maxTileCount = 0;
    for (size_t letterNo=0; letterNo<alphabetLength; ++letterNo)
    {
        for (size_t letterTileNo=0; letterTileNo<tileMaxCounts[letterNo]; ++letterTileNo)
            tilesInBag.push_back(ScrabbleTile(tileChar[letterNo], tileValues[letterNo], remainingTileCount+letterTileNo) );

        remainingTileCount += tileMaxCounts[letterNo];
        maxTileCount += tileMaxCounts[letterNo];
        tileCounts[letterNo] = tileMaxCounts[letterNo];
    }

    shuffle_bag();
}

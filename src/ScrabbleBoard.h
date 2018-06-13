#ifndef SCRABBLEBOARD_H
#define SCRABBLEBOARD_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "ScrabbleTile.h"
#include "DictionaryTrie.h"

class ScrabbleBoardSquare
{
    // A descriptor for each type of square in scrabble. most squares are blank (NONE)
public:
    enum SQUARE_TYPE : uint8_t {
        NONE,           // 0
        DOUBLE_LETTER,  // 1
        TRIPLE_LETTER,  // 2
        DOUBLE_WORD,    // 3
        TRIPLE_WORD,    // 4
        START           // 5
    };

private:
    SQUARE_TYPE squareType;
    ScrabbleTile* squareTile;
    static wchar_t squareLabels[6];
    //size_t row, col;    //don't think needed, probably store in board structure

public:
    ScrabbleBoardSquare(SQUARE_TYPE _squareType) : squareType(_squareType), squareTile(nullptr) {}
    SQUARE_TYPE get_type(void)   { return squareType; }

    char get_type_c(void)  { return squareLabels[static_cast<size_t>(squareType)]; }
    inline bool is_open(void)  { return squareTile == nullptr; }
    void set_tile(ScrabbleTile* pNewTile)  { squareTile = pNewTile; } // this overwrites/removes existing tile. check is_open() first if that's unwanted
    ScrabbleTile* get_tile(void)  { return squareTile; }
};


class ScrabbleBoard
{
private:
    std::vector<ScrabbleBoardSquare> bSquares;  //we'll store a 1D vector and index into it to for the 2D business
    size_t bWidth, bHeight, startPos;
    DictionaryTrie* pDict;

    bool add_board_row(const std::string& rowStr);

public:
    ScrabbleBoard(const std::string& boardFileName="", size_t _bWidth=0, size_t _bHeight=0, DictionaryTrie* _pDict=nullptr);
    bool read_file(const std::string& boardFileName);
    void print_board(void);
    void set_dictionary(DictionaryTrie* _pDict) { pDict = _pDict; }

    ScrabbleBoardSquare* get_square_at_pos(size_t rowNo, size_t colNo);
    ScrabbleTile* get_tile_at_pos(size_t rowNo, size_t colNo);
    void get_row_col_from_pos(size_t pos, size_t& rowNo, size_t&colNo);
    bool place_tile(size_t rowNo, size_t colNo, ScrabbleTile& placedTile);
    bool is_valid_tile(size_t rowNo, size_t colNo, ScrabbleTile& placedTile, char playDir=' ');  //use tile? faster for char
    void get_start_row_col(size_t& rowNo, size_t&colNo) { get_row_col_from_pos(startPos, rowNo, colNo); }
};

#endif // SCRABBLEBOARD_H

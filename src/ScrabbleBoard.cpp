#include "ScrabbleBoard.h"

wchar_t ScrabbleBoardSquare::squareLabels[6] = {'.','d', 't', '²', '³', '*'};

ScrabbleBoard::ScrabbleBoard(const std::string& boardFileName, size_t _bWidth, size_t _bHeight, DictionaryTrie* _pDict) :
    bWidth(_bWidth),
    bHeight(_bHeight),
    pDict(_pDict),
    startPos(0)
{
    if (!boardFileName.empty())
        read_file(boardFileName);
}

bool ScrabbleBoard::read_file(const std::string& boardFileName)
{
    std::ifstream inputFile( boardFileName );
    if (!inputFile.is_open())
        return false;

    std::string rowStr;
    bHeight = 0;
    while (std::getline(inputFile, rowStr, '\n'))
    {
        if (add_board_row(rowStr) )
            ++bHeight;
    }

    return true;
}

bool ScrabbleBoard::add_board_row(const std::string& rowStr)
{
    size_t rowLng = rowStr.size();

    if (bWidth == 0)
        bWidth = rowLng;
    //else if (rowLng != bWidth)
    //    retVal = false;  //report that something is fishy, but fill the row with NONEs (seems reasonable to me)

    for (size_t charNo=0; charNo<rowLng; ++charNo)
    {
        ScrabbleBoardSquare::SQUARE_TYPE iType = static_cast<ScrabbleBoardSquare::SQUARE_TYPE>(rowStr[charNo] - '0' ) ;
        if (iType == ScrabbleBoardSquare::SQUARE_TYPE::START)
            startPos = bSquares.size();

        bSquares.push_back( ScrabbleBoardSquare(iType) );
    }
    if (rowLng != bWidth)
    {

        return false;
    }
    return true;
}


void ScrabbleBoard::print_board(void)
{
    char c;
    ScrabbleTile* pTile;
    for (size_t rowNo=0; rowNo<bHeight; ++rowNo)
    {
        for (size_t colNo=0; colNo<bWidth; ++colNo)
        {
            pTile = get_tile_at_pos(rowNo, colNo);
            if (pTile!=nullptr)
                c = pTile->tileLetter;
            else
                c = get_square_at_pos(rowNo, colNo)->get_type_c();
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}


ScrabbleBoardSquare* ScrabbleBoard::get_square_at_pos(size_t rowNo, size_t colNo)
{
    //make sure requested position is in board domain. *this is pretty sloppy because size_t is unsigned - if row/col goes <0, it wraps and is > bWidth/bHeight...
    if (rowNo >= bWidth ||colNo >= bHeight)
        return nullptr;

    return &(bSquares[bWidth*rowNo + colNo]);
}


ScrabbleTile* ScrabbleBoard::get_tile_at_pos(size_t rowNo, size_t colNo)
{
    //make sure requested position is in board domain. *this is pretty sloppy because size_t is unsigned - if row/col goes <0, it wraps and is > bWidth/bHeight...
    if (rowNo >= bWidth || colNo >= bHeight)
        return nullptr;

    return bSquares[bWidth*rowNo + colNo].get_tile();
}

//get row/col from element in
void ScrabbleBoard::get_row_col_from_pos(size_t pos, size_t& rowNo, size_t& colNo)
{
    rowNo = static_cast<size_t>(pos/bWidth);
    colNo = pos % bWidth;
}


bool ScrabbleBoard::place_tile(size_t rowNo, size_t colNo, ScrabbleTile& placedTile)
{
    ScrabbleBoardSquare* pSquare = get_square_at_pos(rowNo, colNo);

    //can't place the tile if there's already a tile on the square
    if ( !pSquare->is_open() )
        return false;

    pSquare->set_tile(&placedTile);
    return true;
}


bool ScrabbleBoard::is_valid_tile(size_t rowNo, size_t colNo, ScrabbleTile& placedTile, char playDir)
{
    char c;
    //ScrabbleBoardSquare* pSquare;
    ScrabbleTile* pTile;

    //if playing tiles not-horizontally (vertical or other), check if any connections crosswise (horizontal) exist and if so check if they are legal words
    if (playDir != 'h')
    {
        //walk left to beginning of horizontal word (follow adjacent letters until find an empty square)
        //int adjRow = static_cast<int>(rowNo)-1;
        //while ( adjRow>=0 && get_tile_at_pos(adjRow, colNo) != nullptr )
        size_t adjRow = rowNo-1;
        while ( get_tile_at_pos(adjRow, colNo) != nullptr )
            --adjRow;


        c = get_tile_at_pos(++adjRow, colNo)->tileLetter;      //first take one step right (++) because we were at the empty tile 1 square left of last tile
        TrieLeaf* pLeaf = pDict->get_trie_head()->find_leaf(c); //get leaf from 1st letter. We need to pass through the head first

        //now step right until we: 1}hit a blank tile (is word if word_end) or 2}can't find child c from pLeaf (not word)
        while ( pLeaf != nullptr )
        {
//            if (++adjRow >= bWidth)
//                break;

            pTile = get_tile_at_pos(adjRow, colNo);
            //end of horizontal cross word (next square is empty, no tile). We have a pLeaf, good, but we still need to check that we're at the end of a word.
            if ( pTile==nullptr )
                break;

            c = pTile->tileLetter;  //to find the cross word, append c to a str and check that size()>1 at end
            pLeaf = pLeaf->find_leaf(c);
        }

        // cross word is not valid (invalid pleaf or leaf is not a full word)
        if ( pLeaf==nullptr || !pLeaf->is_word_end() )
            return false;

        //otherwise this word is valid, but we'll potentially check other direction too now
    }

    //if playing tiles not-vertically (horizontal or other), check if any connections crosswise (vertical) exist and if so check if they are legal words
    if (playDir != 'v')
    {
        //walk left to beginning of horizontal word (follow adjacent letters until find an empty square)
//        int adjCol = static_cast<int>(colNo)-1;
//        while ( adjCol>=0 && get_tile_at_pos(rowNo, adjCol) != nullptr )
//            --adjCol;
        size_t adjCol = colNo-1;
        while ( get_tile_at_pos(rowNo, adjCol) != nullptr )
            --adjCol;

        c = get_tile_at_pos(rowNo, ++adjCol)->tileLetter;      //first take one step right (++) because we were at the empty tile 1 square left of last tile
        TrieLeaf* pLeaf = pDict->get_trie_head()->find_leaf(c); //get leaf from 1st letter. We need to pass through the head first

        //now step right until we: 1}hit a blank tile (is word if word_end) or 2}can't find child c from pLeaf (not word)
        while ( pLeaf != nullptr )
        {
//            if (++adjCol >= bHeight)
//                break;

            pTile = get_tile_at_pos(rowNo, adjCol);
            //end of horizontal cross word (next square is empty, no tile). We have a pLeaf, good, but we still need to check that we're at the end of a word.
            if ( pTile==nullptr )
                break;

            c = pTile->tileLetter;  //to find the cross word, append c to a str and check that size()>1 at end
            pLeaf = pLeaf->find_leaf(c);
        }

        // cross word is not valid (invalid pleaf or leaf is not a full word)
        if ( pLeaf==nullptr || !pLeaf->is_word_end() )
            return false;

        //otherwise this word is valid, but we'll potentially check other direction too now
    }

    //if we didn't find a problem, the word is good
    return true;
}

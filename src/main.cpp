//#include "MainWindowScrabble.h"
#include "DictionaryTrie.h"
#include "ScrabbleBoard.h"
#include "TileBag.h"
#include "ScrabbleHand.h"

#include <QApplication>
#include <chrono>

int main(int argc, char** argv) {
//    QApplication app(argc, argv);
//    MainWindowScrabble sWindow;
//    sWindow.show();
//    return app.exec();

    auto t0 = std::chrono::high_resolution_clock::now();

    DictionaryTrie dict("../data/dictionary_twl06.txt");

    auto t1 = std::chrono::high_resolution_clock::now();

//    dict.print_trie();
//    std::cout << "KK 0" << std::endl;

//    std::cout << dict.is_word("IATROGENICALLY") << std::endl;
//    std::cout << dict.is_word("I") << std::endl;
//    std::cout << dict.is_word("IA") << std::endl;
//    std::cout << dict.is_word("JACKAL") << std::endl;

    TileBag tBag("../data/tiles_EnUS.txt");
    ScrabbleHand myHand(7);
    myHand.draw_to_fill(tBag);
    std::string handStr;
    myHand.get_letters(handStr);

    std::cout << "My orig hand: " << myHand << std::endl;

    auto t20 = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<ScrabbleTile*>> outPlays;
    std::vector<std::string> outWords;

    dict.build_words_from_string(handStr, outWords, true);
    dict.build_words_from_hand(myHand.tilesInHand, outPlays, false);

    auto t21 = std::chrono::high_resolution_clock::now();

    ScrabbleBoard scrabBoard("../data/board_scrabble.txt");

    auto t3 = std::chrono::high_resolution_clock::now();

    std::cout << "build trie:  " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;
    std::cout << "bag + hand:  " << std::chrono::duration_cast<std::chrono::milliseconds>(t20 - t1).count() << std::endl;
    std::cout << "check words: " << std::chrono::duration_cast<std::chrono::milliseconds>(t21 - t20).count() << std::endl;
    std::cout << "read board:  " << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t21).count() << std::endl;

    std::vector<ScrabbleTile*> bestWord;
    size_t bestScore=0;
    for (std::vector<ScrabbleTile*>& playTiles : outPlays)
    {
        uint16_t score = 0;
        for (ScrabbleTile* pTile : playTiles)  score += pTile->tileValue;
        if (score > bestScore)
        {
            bestScore = score;
            bestWord = playTiles;
        }
    }

    std::string playStr(bestWord.size(), ' ');
    for (size_t tileNo=0; tileNo<bestWord.size(); ++tileNo)
        playStr[tileNo] = bestWord[tileNo]->tileLetter;

    std::cout << "best play: " <<  playStr << "  " << bestScore << "pts" << std::endl;

    size_t row, col;
    scrabBoard.get_start_row_col(row, col);
    for (ScrabbleTile* pTile : bestWord)
    {
        scrabBoard.place_tile(row++, col, *pTile);
        myHand.remove_from_hand(pTile);
    }

    std::cout << "My new hand: " << myHand << std::endl;

    scrabBoard.print_board();

    return 0;
}

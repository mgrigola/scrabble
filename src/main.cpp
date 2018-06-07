//#include "MainWindowScrabble.h"
#include "DictionaryTrie.h"

#include <QApplication>

int main(int argc, char** argv) {
//    QApplication app(argc, argv);
//    MainWindowScrabble sWindow;
//    sWindow.show();
//    return app.exec();

    DictionaryTrie dict("../data/twl06.txt");
//    dict.print_trie();
//    std::cout << "KK 0" << std::endl;

//    std::cout << dict.is_word("IATROGENICALLY") << std::endl;
//    std::cout << dict.is_word("I") << std::endl;
//    std::cout << dict.is_word("IA") << std::endl;
//    std::cout << dict.is_word("JACKAL") << std::endl;

    std::string anagramStr = "?CZAR";
    std::vector<std::string> outWords;
    dict.build_words_from_word(anagramStr, outWords);

    return 0;
}

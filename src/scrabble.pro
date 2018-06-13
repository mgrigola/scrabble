QT       += widgets

QMAKE_CXXFLAGS +=   -Wno-reorder

TARGET = scrabble

HEADERS +=  \
    MainWindowScrabble.h \
    ScrabbleTile.h \
    TileBag.h \
    ScrabbleHand.h \
    DictionaryTrie.h \
    ScrabbleBoard.h \
    ScrabbleMove.h \
    ScrabbleBlankTile.h \
    TileSequence.h

SOURCES +=  main.cpp \
    MainWindowScrabble.cpp \
    TileBag.cpp \
    ScrabbleHand.cpp \
    DictionaryTrie.cpp \
    ScrabbleBoard.cpp \
    ScrabbleMove.cpp \
    TileSequence.cpp


INCLUDEPATH += "../../qt_common/opencv/include"

#comment
LIBS += -L"../../qt_common/opencv/x86/mingw/lib" \
        -lopencv_highgui310 \
        -lopencv_core310 \
        -lopencv_imgcodecs310 \
        -lopencv_imgproc310 \
        -lopencv_calib3d310 \
        -lopencv_ml310

QT       += widgets

QMAKE_CXXFLAGS +=   -Wno-reorder

TARGET = scrabble

HEADERS +=  \
    MainWindowScrabble.h \
    ScrabbleTile.h \
    TileBag.h \
    ScrabbleHand.h \
    DictionaryTrie.h

SOURCES +=  main.cpp \
    MainWindowScrabble.cpp \
    TileBag.cpp \
    ScrabbleHand.cpp \
    DictionaryTrie.cpp


INCLUDEPATH += "C:/Users/m/Documents/GitHub/Qt/common/build/include"

LIBS += -L"C:/Users/m//Documents/GitHub/Qt/common/build/x86/mingw/lib" \
        -lopencv_highgui310 \
        -lopencv_core310 \
        -lopencv_imgcodecs310 \
        -lopencv_imgproc310 \
        -lopencv_calib3d310 \
        -lopencv_ml310

#include "MainWindowScrabble.h"

MainWindowScrabble::MainWindowScrabble(QWidget* _parent)
{    
    this->setParent(_parent);
    this->setWindowTitle("Scrabble!");

    gLayoutMain = new QGridLayout();  // careful setting parent - it applies this layout for the target widget
    gLayoutMain->setContentsMargins(4,4,4,4);
    setLayout(gLayoutMain);

    QTableWidget* tableWidgetOutputWords = new QTableWidget(this);
    tableWidgetOutputWords->setRowCount(1);
    tableWidgetOutputWords->setColumnCount(1);
    gLayoutMain->addWidget(tableWidgetOutputWords, 0, 0, 1, TILES_IN_HAND, Qt::AlignCenter);

    //QFont tileFont(QFont::SansSerif, 24, 2, false);
    QFont tileFont;
    tileFont.setStyleHint(QFont::SansSerif);
    tileFont.setPointSize(24);
    tileFont.setWeight(2);

    for (size_t tileNo=0; tileNo<TILES_IN_HAND; ++tileNo)
    {
        labelLetterTiles[tileNo] = new QLabel(" ", this);
        labelLetterTiles[tileNo]->setFont(tileFont);
        gLayoutMain->addWidget(labelLetterTiles[tileNo], 1, tileNo, 1, 1, Qt::AlignCenter);
    }

//    connect( pushButtonSolve, SIGNAL(clicked(bool)), sudokuTable, SLOT(Solve_Board()) );
//    connect( comboBoxFileSelect, SIGNAL(activated(QString)), this, SLOT(Update_Display_Puzzle_Number(QString)));

//    connect( pushButtonSlowSolve, SIGNAL(clicked(bool)), this, SLOT(Slow_Solve()) );
//    connect( pushButtonPauseSolve, SIGNAL(clicked(bool)), this, SLOT(Pause_Solve()) );
//    connect( this, SIGNAL(Send_Pause()), sudokuTable, SLOT(Pause_Solve()) );
//    connect( this, SIGNAL(Send_Slow_Solve()), sudokuTable, SLOT(Slow_Solve()) );
//    connect( sudokuTable, SIGNAL(Solve_Done()), this, SLOT(Solve_Done()) );

    //comboBoxFileSelect->setCurrentIndex(1);
    //emit( comboBoxFileSelect->activated( comboBoxFileSelect->currentText()) );

    //Read_Sudoku_Board_Image();
    //Read_Sudoku_Board_File();
    //Create_Legend_Window();
}


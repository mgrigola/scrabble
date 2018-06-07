#ifndef SCARABBLEWINDOW_H
#define SCARABBLEWINDOW_H

#define TILES_IN_HAND 7

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QDir>
#include <QFile>
#include <QString>
#include <QSpinBox>
#include <QTableWidget>
#include <QFont>

class MainWindowScrabble : public QWidget
{
    Q_OBJECT
private:
    QPushButton* pushButtonDrawTiles;
    QLabel* labelLetterTiles[7];
    QTableWidget* tableWidgetOutputWords;
    QGridLayout* gLayoutMain;

public:
    MainWindowScrabble(QWidget* _parent = 0);

signals:

private slots:

};

#endif

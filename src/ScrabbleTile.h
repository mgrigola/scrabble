#ifndef SCRABBLETILE_H
#define SCRABBLETILE_H


class ScrabbleTile
{
private:
    unsigned int tileID;

public:
    char tileLetter;
    unsigned int tileValue;
    ScrabbleTile(char _letter='0', unsigned int _value=0, unsigned int _id=0) :
        tileLetter(_letter),
        tileValue(_value),
        tileID(_id)
    { }
    ScrabbleTile(const ScrabbleTile& other) { tileLetter = other.tileLetter; tileValue = other.tileValue; tileID = other.tileID; }
    //char get_letter(void)  { return tileLetter; }
    //unsigned int get_value(void)  { return tileValue; }
};

#endif // SCRABBLETILE_H

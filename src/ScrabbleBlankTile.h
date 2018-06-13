#ifndef SCRABBLEBLANKTILE_H
#define SCRABBLEBLANKTILE_H

#include "ScrabbleTile.h"

class ScrabbleBlankTile : public ScrabbleTile
{
public:
    char usedLetter;   // blank has value '?', but we use it as usedLetter

    ScrabbleBlankTile(char _letter='0', unsigned int _value=0, unsigned int _id=0, char _usedLetter='0') :
        ScrabbleTile(_letter, _value, _id),
        usedLetter(_usedLetter)
    { }
    ScrabbleBlankTile(const ScrabbleBlankTile& other) : ScrabbleTile(other), usedLetter(other.usedLetter) { }
    ScrabbleBlankTile(const ScrabbleTile& other) : ScrabbleTile(other), usedLetter('?') { }

    virtual char get_letter(void) { return usedLetter; }  //overrides default of returning tileLetter, returns letter we're using it as
};

#endif // SCRABBLEBLANKTILE_H

#ifndef TILESEQUENCE_H
#define TILESEQUENCE_H

#include "ScrabbleTile.h"

class TileSequenceNode
{
public:
    TileSequenceNode(ScrabbleTile* _pVal, TileSequenceNode* _pPrev=nullptr) : pVal(_pVal), pPrev(_pPrev) {}
    ScrabbleTile* pVal;
    TileSequenceNode* pPrev;
};

class TileSequence
{
public:
    TileSequence() : pHead(nullptr), pTail(nullptr) {}
    TileSequenceNode* pHead, *pTail;
    void insert_before(ScrabbleTile* pAddedVal, TileSequenceNode* insertBeforeNode=nullptr);
    ScrabbleTile* remove_before(TileSequenceNode* removeAfterThisNode=nullptr);
};

#endif // TILESEQUENCE_H

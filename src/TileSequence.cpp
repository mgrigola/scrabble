#include "TileSequence.h"

//if appendAfterThisNode == nullptr, append at head (before current head)
void TileSequence::insert_after(ScrabbleTile* pAddedVal, TileSequenceNode* insertBeforeNode=nullptr)
{
    TileSequenceNode* pNewNode = new TileSequenceNode(pAddedVal);

    //if no insert-before-this-node given, insert after tail (append)
    if (insertBeforeNode == nullptr)
    {
        pNewNode->pPrev = pTail;
        pTail = newNode;
    }
    else
    {
        pNewNode->pPrev = insertBeforeNode->pPrev;
        insertBeforeNode->pPrev = pNewNode;
    }

    if (pHead == nullptr || pHead == insertBeforeNode)
        pHead = pNewNode;
}


//if removeAfterThisNode == nullptr, remove head
ScrabbleTile* TileSequence::remove_before(TileSequenceNode* removeBeforeNode=nullptr)
{
    TileSequenceNode* pRemoved;

    //if no remove-before-this-node given, remove tail
    if (removeBeforeNode == nullptr)
    {
        //if no items in sequence, return null
        if (pTail == nullptr)
            return nullptr;

        pRemoved = pTail;
        pTail = pTail->pPrev;
    }
    else
    {
        pRemoved = removeBeforeNode->pPrev;
        removeBeforeNode->pPrev = pRemoved->pPrev;

    }

    //if we removed head, set head to removeBeforeNode. If removeBeforeHead was nullptr (we removed tail) then the list is now empty and head=tail=null
    if (pRemoved == pHead)
        pHead = removeBeforeNode;

    ScrabbleTile* pRetTile = pRemoved->pVal;
    delete *pRemoved;

    return pRetTile;
}



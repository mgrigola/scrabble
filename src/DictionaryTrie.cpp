#include "DictionaryTrie.h"

//binary search links for c. links (vector) is stored sorted by target value (the letter it links to).
bool TrieLeaf::contains(const char cTgt, TrieLeaf& leafLink)
{
    size_t N = links.size();
    //no current links. Trying to avoid unsigned = -1
    if (N == 0)
        return false;

    //basic binary search
    size_t lowIdx=0, highIdx=N-1;
    char leafVal;
    while (lowIdx < highIdx)
    {
        //new idx is midpoint of potential range, binary search
        size_t idx = static_cast<size_t>((lowIdx+highIdx)/2);
        leafVal = links[idx]->val;

        if (cTgt > leafVal)         //target greater than mid item, search upper half
        {
            lowIdx = idx+1;
        }
        else if (cTgt == leafVal)   //found target, already exists
        {
            leafLink = *links[idx];
            return true;
        }
        else                        //target less than mid item, search lower half
        {
            if (idx==0)             //beware unsigned overflow, 0-1 = 2^32. this happens after lowIdx=0, highIdx=1, val<leafVal(lowIdx)
                return false;
            highIdx = idx-1;
        }
    }

    //we break above when low==high. we still need to check if links[low (or high)] is the target
    leafVal = links[lowIdx]->val;
    if (leafVal == cTgt)
    {
        leafLink = *links[lowIdx];
        return true;
    }

    return false;
}

TrieLeaf* TrieLeaf::contains_create(const char cTgt)
{
    TrieLeaf* pLeaf;
    size_t lowIdx=0, highIdx=links.size();

    //no current links. this new leaf will be the first. Trying to avoid unsigned = -1
    if (highIdx == 0)
    {
        pLeaf = new TrieLeaf(cTgt, this);
        this->links.push_back(pLeaf);
        return pLeaf;
    }
    else  --highIdx;

    //basic binary search
    char leafVal;
    while (lowIdx < highIdx)
    {
        //new idx is midpoint of potential range, binary search
        size_t idx = static_cast<size_t>((lowIdx+highIdx)/2);
        pLeaf = links[idx];
        leafVal = pLeaf->val;
        if (cTgt > leafVal)         lowIdx = idx+1;  //target greater than mid item, search upper half
        else if (cTgt == leafVal)   return pLeaf;    //found target, already exists
        else                        highIdx = idx-1; //target less than mid item, search lower half
    }

    //we break above when low==high. we still need to check if links[low (or high)] is the target
    pLeaf = links[lowIdx];
    leafVal = pLeaf->val;
    if (leafVal == cTgt)
        return pLeaf;

    // cTgt is not in this TrieLeaf, we need to create a new leaf for cTgt and add it to this
    if (cTgt > leafVal)  lowIdx += 1;  //if target greater than closet existing element, place after it. else place before (we'll shift v back)
    pLeaf = new TrieLeaf(cTgt, this);

    //this->links is sorted on val/character (key). We know pLeaf belongs at links[lowIdx] (=highIdx)
    //we need to push everything after that back 1 and insert. we push_back with leaf to expand links size, we will place it correctly at end
    links.push_back(pLeaf);
    for (size_t shiftIdx=links.size()-1; shiftIdx>lowIdx; --shiftIdx)
        this->links[shiftIdx] = this->links[shiftIdx-1];
    links[lowIdx] = pLeaf;

    return pLeaf;
}

std::string TrieLeaf::get_child_letters(void)
{
    std::string retString = "";
    for (TrieLeaf* pLeaf : links)
        retString += pLeaf->val;

    return retString;
}


std::string TrieLeaf::get_parent_word(void)
{
    std::string retStr(1, this->val);  //construct string from sngle char: need to provide the length as first argument
    TrieLeaf* parent = this->pParent;
    char v = parent->val;
    while (v != '\0')       // Trie head has value '\0' (null). everything else should be a char
    {
        retStr = v + retStr;
        parent = parent->pParent;
        v = parent->val;
    }
    return retStr;
}

void TrieLeaf::get_parent_word_r(std::string& parentWord)
{
    if (val == '\0')
    {
        //std::reverse(parentWord.begin(), parentWord.end()); //include <algorithm>
        size_t N = parentWord.size();
        for (size_t charNo=0; charNo<static_cast<size_t>(N/2); ++charNo)  std::swap(parentWord[charNo], parentWord[N-charNo-1] );
        return;
    }
    parentWord += val;
    pParent->get_parent_word_r(parentWord);
}


DictionaryTrie::DictionaryTrie(const std::string& dictFileName) :
    trieHead( )
{
//    for (char c='A'; c<='Z'; ++c)
//        trieHead.contains_create(c);

    if (!dictFileName.empty())
        read_file(dictFileName);
}


bool DictionaryTrie::read_file(const std::string& dictFileName)
{
    std::ifstream inputFile( dictFileName );
    if (!inputFile.is_open())
        return false;

    std::string wordStr;
    while (std::getline(inputFile, wordStr, '\n'))
    {
        add_word(wordStr);
    }
    return true;
}

bool DictionaryTrie::add_word(const std::string& wordStr)
{
    TrieLeaf* pLeaf = &trieHead;
    for (const char c : wordStr)
        pLeaf = pLeaf->contains_create(c);


    pLeaf->set_word_end();
    return true;
}


bool DictionaryTrie::is_word(const std::string& wordStr)
{
    TrieLeaf leafLink = trieHead;
    for (const char c : wordStr)
        if ( !leafLink.contains(c, leafLink) )
            return false;

    return leafLink.is_word_end();
}


//we probably want to check if curLeaf actually has children (links)
//possibly we want to loop over curLeaf's links if count(links) < count(remainingLetters) ?
//probably wanna divide out some pieces as separate functions to make "?"/blank handling not a mess
void DictionaryTrie::build_words_from_set_r(TrieLeaf* curLeaf, const std::vector<char>& remainingLetters, std::vector<std::string>& outputWords)
{
    size_t N = remainingLetters.size();
    TrieLeaf newLeaf;
    for (size_t charNo=0; charNo<N; ++charNo)
    {
        char c = remainingLetters[charNo];
        //prevent duplicates
        //ex with {ccdee} we could create 'cede' starting from either 'c', but below skips recursion on the second c (and double e's)
        // still allows 'cee', 'cede' where the duplicate letters occur at different positions
        if (charNo>0 && remainingLetters[charNo-1]==c)
            continue;

        //handle blanks? they can be any letter, so follow any children of leaf and
        if (c == '?')
        {
            size_t linkNo = 0;
            TrieLeaf* pQLeaf = curLeaf->get_child_at(linkNo);

            //make sure curLeaf actually has children
            if (pQLeaf == nullptr)
                continue;

            std::vector<char> newQLetters(N-1);
            if ( N > 1 )
            {
                for (size_t copyCharNo=0; copyCharNo<charNo; copyCharNo++)
                    newQLetters[copyCharNo] = remainingLetters[copyCharNo];
                for (size_t copyCharNo=charNo+1; copyCharNo<N; copyCharNo++)
                    newQLetters[copyCharNo-1] = remainingLetters[copyCharNo];

                build_words_from_set_r(pQLeaf, newQLetters, outputWords);
            }

            while (pQLeaf != nullptr)
            {
                if (pQLeaf->is_word_end())
                {
                    std::string parentWord = "";
                    pQLeaf->get_parent_word_r(parentWord);
                    size_t wrdSz = parentWord.size();
                    parentWord[wrdSz-1] = '[';
                    parentWord += pQLeaf->get_val();
                    parentWord += "?]";

                    outputWords.push_back(parentWord);
                }
                //only recurse if more letters in 'hand'
                //note the new remaining letters are the same regardless of what value ? takes (we don't redefine/change newQLetters in this while loop, just once before)
                if ( N > 1 )
                    build_words_from_set_r(pQLeaf, newQLetters, outputWords);

                ++linkNo;
                pQLeaf = curLeaf->get_child_at(linkNo);  //return nullptr when linkNo = links/size();  links is private
            }

            continue;
        }

        //check each letter in our current letter list. see if curLeaf has a link to the letter. If not, this branch is dead end, try other letters
        if ( !curLeaf->contains(c, newLeaf) )
            continue;

        if (newLeaf.is_word_end())
        {
            std::string parentWord = "";
            newLeaf.get_parent_word_r(parentWord);
            outputWords.push_back(parentWord);
        }

        // if 1 char left, we can't go any deeper. we just checked if this last letter forms a word. this is end of the line
        if ( N <= 1 )
            return;

        //if currentNode has link to letters[charNo]. keep traversing down. update remaing letters to remove the letter we moved to
        //create a sub'string' (vector) from letters minus the current charNo letter
        std::vector<char> newLetters(N-1);
        for (size_t copyCharNo=0; copyCharNo<charNo; copyCharNo++)
            newLetters[copyCharNo] = remainingLetters[copyCharNo];
        for (size_t copyCharNo=charNo+1; copyCharNo<N; copyCharNo++)
            newLetters[copyCharNo-1] = remainingLetters[copyCharNo];

        build_words_from_set_r(&newLeaf, newLetters, outputWords);
    }

}


void DictionaryTrie::build_words_from_set(const std::vector<char>& wordLetters, std::vector<std::string>& outputWords)
{
    build_words_from_set_r(&trieHead, wordLetters, outputWords);
    std::sort(outputWords.begin(), outputWords.end() );
    size_t charCnt=0, maxCharsInRow=128, strSz;
    char lastChar = ' ';
    for (std::string str : outputWords)
    {
        strSz = str.size() + 1;
        charCnt += strSz;
        if (charCnt > maxCharsInRow || str[0]!=lastChar)
        {
            std::cout << std::endl;
            if (charCnt > maxCharsInRow)  std::cout << "\t";
            charCnt = strSz;
            lastChar = str[0];
        }
        std::cout << str << " ";
    }
    std::cout << std::endl;
}


//bool my_sort_func (char i,char j) { return (i<j); }
void DictionaryTrie::build_words_from_word(const std::string& wordStr, std::vector<std::string>& outputWords)
{
    std::vector<char> wordLetters(wordStr.begin(), wordStr.end() );
    std::sort( wordLetters.begin(), wordLetters.end());
    build_words_from_set(wordLetters, outputWords);
}


void DictionaryTrie::print_trie(void)
{
    std::string childLetters;
    childLetters = trieHead.get_child_letters();
    for (char letter : childLetters)
    {
        std::cout << letter << " - ";
        TrieLeaf* pLeaf = trieHead.contains_create(letter);
        std::cout << pLeaf->get_child_letters() << std::endl;
    }
}

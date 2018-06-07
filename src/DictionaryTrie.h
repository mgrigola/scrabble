#ifndef DICTIONARYTRIE_H
#define DICTIONARYTRIE_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>


class TrieLeaf
{
private:
    char val; //key
    TrieLeaf* pParent;
    std::vector<TrieLeaf*> links;
    bool isWord;
public:
    TrieLeaf(char _val='\0', TrieLeaf* _pParent=nullptr) : val(_val), pParent(_pParent), isWord(false), links()  { }
    void set_word_end(void)  { isWord = true; }
    bool is_word_end(void)  { return isWord; }
    bool is_linkless(void)  { return (links.size()==0); }
    size_t link_count(void)  { return links.size(); }
    bool contains(char c, TrieLeaf& leafLink);
    TrieLeaf* contains_create(char cTgt);
    std::string get_child_letters(void);
    std::string get_parent_word(void);
    void get_parent_word_r(std::string& parentWord);

    TrieLeaf* get_child_at(size_t linkNo) {return linkNo<links.size() ? links[linkNo] : nullptr; }
    char get_val(void)  { return val; }
};



class DictionaryTrie
{
private:
    TrieLeaf trieHead;
    void build_words_from_set_r(TrieLeaf* curLeaf, const std::vector<char>& letters, std::vector<std::string>& outputWords);

public:
    DictionaryTrie(const std::string& dictFileName="");
    //~DictionaryTrie();  //delete all the links...
    bool read_file(const std::string& dictFileName);
    bool add_word(const std::string& wordStr);

    bool is_word(const std::string& wordStr);
    void build_words_from_set(const std::vector<char>& wordLetters, std::vector<std::string>& outputWords);
    void build_words_from_word(const std::string& wordStr, std::vector<std::string>& outputWords);
    void print_trie(void);
};

#endif // DICTIONARYTRIE_H

#ifndef WORD_TREE_H
#define WORD_TREE_H

#include <string>
#include <stdlib.h>
#include <iostream>

class WordTree
{

private:
    const static unsigned int NUM_LETTERS = 26;
    void addWordToTree(const std::string *word, unsigned int index);
    std::string printTree(std::string currWord) const;

    short minWordLength;
    short maxWordLength;

public:
    WordTree() : WordTree(4, 15) {}
    WordTree(short minWl, short maxWl) : isWord(false), minWordLength(minWl), maxWordLength(maxWl)
    {
        for (auto i = 0; i < NUM_LETTERS; i++)
        {
            this->paths[i] = NULL;
        }
    }
    ~WordTree()
    {
        for (auto i = 0; i < NUM_LETTERS; i++)
        {
            delete this->paths[i];
        }
    }
    bool isWord = false;
    WordTree *paths[NUM_LETTERS];

    bool addWordToTree(const std::string *word);
    std::string printTree() const;
};

void WordTree::addWordToTree(const std::string *word, unsigned int index)
{
    if (!word)
        return;

    if (index >= word->length())
    {
        this->isWord = true;
        return;
    }

    char currentLetter = (*word)[index];
    unsigned int char_to_index = currentLetter - 'a';

    if (char_to_index >= NUM_LETTERS)
        return;

    if (!this->paths[char_to_index])
    {
        this->paths[char_to_index] = new WordTree();
    }
    this->paths[char_to_index]->addWordToTree(word, index + 1);
}

bool WordTree::addWordToTree(const std::string *word)
{
    auto len = word->length();
    if (len < this->minWordLength || len > this->maxWordLength)
    {
        return false;
    }

    addWordToTree(word, 0U);
    return true;
}

std::string WordTree::printTree(std::string currWord) const
{
    std::string result = std::string("");
    if (this->isWord)
    {
        result += currWord + "\n";
    }
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (!this->paths[i])
            continue;

        std::string newWord = std::string(currWord);

        newWord += ((char)i + 'a');
        result += this->paths[i]->printTree(newWord);
    }
    return result;
}

std::string WordTree::printTree() const
{
    return this->printTree(std::string(""));
}

std::ostream &operator<<(std::ostream &os, const WordTree &wt)
{
    return (os << wt.printTree());
}
#endif
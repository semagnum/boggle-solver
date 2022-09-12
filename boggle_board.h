#ifndef BOGGLE_BOARD_H
#define BOGGLE_BOARD_H

#include <iostream>

class BoggleBoard
{
private:
    const static short VOWEL_SIZE = 6;
    const static short CONSONANT_SIZE = 20;
    const static char VOWELS[VOWEL_SIZE];
    const static char CONSONANTS[CONSONANT_SIZE];
    void jumble();

public:
    const static unsigned short SIZE = 4;
    char board[SIZE][SIZE];

    BoggleBoard() { jumble(); }
    BoggleBoard(char setBoard[][SIZE])
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                this->board[i][j] = setBoard[i][j];
            }
        }
    };
};

const char BoggleBoard::VOWELS[] = {'a', 'e', 'i', 'o', 'u', 'y'};
const char BoggleBoard::CONSONANTS[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};

void BoggleBoard::jumble()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            char choice;
            auto isConsonants = (rand() % 2 == 0);
            if (isConsonants)
                choice = VOWELS[rand() % VOWEL_SIZE];
            else
                choice = CONSONANTS[rand() % CONSONANT_SIZE];
            this->board[i][j] = choice;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const BoggleBoard &dt)
{
    auto boardSize = BoggleBoard::SIZE;
    os << " -";
    for (auto i = 0; i < boardSize; i++)
    {
        os << "--";
    }
    os << std::endl;
    for (auto i = 0; i < boardSize; i++)
    {
        os << "| ";
        for (auto j = 0; j < boardSize; j++)
        {
            os << dt.board[i][j] << " ";
        }
        os << "|" << std::endl;
    }
    os << " -";
    for (auto i = 0; i < boardSize; i++)
    {
        os << "--";
    }
    os << std::endl;
    return os;
}

#endif
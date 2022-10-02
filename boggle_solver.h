#ifndef BOGGLE_SOLVER_H
#define BOGGLE_SOLVER_H

#include <string>
#include <vector>
#include <set>

#include "boggle_board.h"
#include "word_tree.h"

class BoggleSolver
{
private:
    const BoggleBoard *board;
    const WordTree *wordTree;
    void solve(const unsigned short row, const unsigned short col, const WordTree *wordTree, std::string currWord, std::set<std::string> *words);
    std::vector<std::vector<bool>> visited;

public:
    BoggleSolver(const BoggleBoard *b, const WordTree *wt) : board(b), wordTree(wt)
    {
        int size = BoggleBoard::SIZE;
        std::vector<bool> row(size, false);

        for (int i = 0; i < size; i++)
        {
            visited.push_back(row);
        }
    }
    std::set<std::string> solve();
};

std::set<std::string> BoggleSolver::solve()
{
    std::set<std::string> wordList;
    for (unsigned short row = 0; row < BoggleBoard::SIZE; row++)
    {
        for (unsigned short col = 0; col < BoggleBoard::SIZE; col++)
        {
            this->solve(row, col, this->wordTree, std::string(""), &wordList);
        }
    }


    return wordList;
}

void BoggleSolver::solve(const unsigned short row, const unsigned short col, const WordTree *wordTree, std::string currWord, std::set<std::string> *words)
{
    this->visited[row][col] = true;

    if (wordTree->isWord) {
        words->insert(currWord);
    }
    
    // for each of the adjacent cells
    for (short row_offset = -1; row_offset <= 1; row_offset++)
    {
        for (short col_offset = -1; col_offset <= 1; col_offset++)
        {
            if (col_offset == 0 && row_offset == 0) continue; // cell goes to itself

            // get character
            const unsigned short board_row = (short) row - row_offset;
            const unsigned short board_col = (short) col - col_offset;

            // out of bounds check
            if (board_row >= BoggleBoard::SIZE || board_col >= BoggleBoard::SIZE)
                continue;

            // already visited
            if (this->visited[board_row][board_col])
                continue; 

            // converts adjacent cell's character to WordTree index            
            char cellLetter = this->board->board[board_row][board_col];
            unsigned int char_to_index = cellLetter - 'a';

            if (wordTree->paths[char_to_index]) {

                const WordTree *child = wordTree->paths[char_to_index];
                //recursively solve
                std::string newWord = std::string(currWord);
                newWord += cellLetter;
                solve(board_row, board_col, child, newWord, words);
            }
        }
    }

    this->visited[row][col] = false;
}

#endif
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "boggle_board.h"
#include "word_tree.h"
#include "boggle_solver.h"

void initializeWordTree(WordTree *wordTree)
{
    auto wordCount = 0;
    std::fstream dictFile;
    dictFile.open("dictionary.txt", std::ios::in);
    if (dictFile.is_open())
    {
        std::string line;
        while (getline(dictFile, line))
        {
            std::stringstream ss(line);
            std::string trimmed_string;
            ss >> trimmed_string;
            if (wordTree->addWordToTree(&trimmed_string))
            {
                wordCount++;
            }
        }
        dictFile.close(); // close the file object.
        std::cout << wordCount << " words added to dictionary\n";
    }
}

int main()
{
    WordTree *wordTree = new WordTree();

    initializeWordTree(wordTree);

    BoggleBoard *myBoard = new BoggleBoard();
    std::cout << BoggleBoard::SIZE << "x" << BoggleBoard::SIZE << " board" << std::endl;
    std::cout << *myBoard;

    BoggleSolver *solver = new BoggleSolver(myBoard, wordTree);

    auto wordList = solver->solve();
    auto wordItr = wordList.begin();

    while (wordItr != wordList.end())
    {
        std::cout << *wordItr << "\n";
        ++wordItr;
    }

    delete(solver);
    delete(wordTree);
    delete(myBoard);


    return 0;
}

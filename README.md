# Boggle Solver

## How to Use

### Provide a Dictionary File
This is simply a plain text file, where each line is its own word (lower case alphabetical letters only) - no empty lines. For example:

```
apple
cat
dictionary
test
```

The given dictionary name used by the app is ```"dictionary.txt"```, but you can change the name as needed in ```"main.cc"```:

```cpp
dictFile.open("large_dictionary.txt", std::ios::in);
```

### Initialize Boggle Board
*Note: each cell only supports single characters; no cell can have multiple letters, e.g. "Qu".*

The default board dimensions are 4x4. If you would like to adjust the size, adjust the ```SIZE``` variable in ```boggle_board.h```.

If you already have a board in mind, initialize it as a 2D char array, like so:
```cpp
char initializedBoard[BoggleBoard::SIZE][BoggleBoard::SIZE] {{'o', 'e', 's', 't'},
                                                            {'g', 'a', 'n', 'i'},
                                                            {'n', 'u', 'l', 'l'},
                                                            {'s', 'a', 'p', 'q'}};
BoggleBoard *myBoard = new BoggleBoard(initializedBoard);
```

Otherwise, you can provide no arguments and it will randomly generate a board:
```cpp
BoggleBoard *myBoard = new BoggleBoard();
```

## How Does It Work?
To initialize the dictionary of words, the program reads each line from the dictionary and adds words to ```WordTree``` - a variation on the [trie data structure](https://en.wikipedia.org/wiki/Trie).

The solver, when passed a ```BoggleBoard``` and ```WordTree``` as references, initializes a same-size board to track board cells that are visited. Its ```solve()``` calls a recursive version of itself, containing the current board position, current ```WordTree``` node, and the current word so far. At each cell, the solver traverses to every adjacent cell, unless said cell has been already visited in the current traversal. Any words found are added to a set and returned.

> Wait, wouldn't this take exponentially forever? For each board cell, the solver traverses every possible path it can on the board?

No, it does not: the solver's ability to traverse the board is bounded by the dictionary and the solver's current ```WordTree``` node and its children. For a minimal example, say your word tree is simply **C->A->T->S**. If you have traversed "cat", the only valid cells the solver will traverse to is cells containing "s". Otherwise, the recursive function will return without traversing further. So unless you provide a dictionary that is just every possible alphabetical combination, the solver will *not* traverse every cell.
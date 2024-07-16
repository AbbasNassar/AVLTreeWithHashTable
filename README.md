# AVL Tree and Hash Table Project

This project demonstrates the implementation of an AVL tree and a hash table in C. The AVL tree is used to store words along with their frequencies and maintain balance for efficient search, insertion, and deletion operations. The hash table employs quadratic probing to handle collisions but lacks re-hashing functionality.

## General Notes
* The delete function for the AVL tree does not rebalance the tree after deletion.
* If a word to be deleted from the tree has more than one frequency, the frequency is decremented until it reaches one, then the node is deleted.
* Words longer than 5 characters can cause integer overflow, leading to a negative index.
* For the hash table, collisions are handled by quadratic probing.
* Re-hashing is not implemented in this code.

## Code Structure
**`main.c`**
This file contains the main function and the menu-driven interface for interacting with the AVL tree and hash table.
### AVL Tree Functions
* `makeEmpty`: Frees the memory allocated for the AVL tree.
* `findNode`: Finds a specific node in the tree, returns NULL if not found.
* `findMinNode`: Finds the minimum node in a branch, used for the delete function.
* `heightOfTree`: Finds the height of a specific branch in the tree.
* `maxOfHeights`: Finds the maximum height between the left and right branches, used in rotation functions.
* `singleRotateWithLeft`: Performs a single left rotation on a subtree.
* `singleRotateWithRight`: Performs a single right rotation on a subtree.
* `doubleRotateWithLeft`: Performs a double left rotation on a subtree.
* `doubleRotateWithRight`: Performs a double right rotation on a subtree.
* `insertNode`: Inserts a node into the AVL tree.
* `printTree`: Prints the words and frequencies of each node in the tree (in-order).
* `deleteNode`: Deletes a node from the tree.
### Hash Table Functions
* `createHashNode`: Creates a hash node from an AVL tree node.
* `stringHashing`: Hashes an input string using quadratic probing.
* `hashWord`: Inserts a word into the hash table.
* `traverseHashing`: Inserts all words from the AVL tree into the hash table.
* `searchHashTable`: Searches for a specific node in the hash table.
* `deleteHashTable:` Deletes a specific node from the hash table.

## Usage
### Menu Options
* `Load data from the file`: Loads data from the input.txt file.
* `Create the AVL tree`: Creates the AVL tree from the data loaded.
* `Insert a word into the AVL tree`: Prompts the user to enter a word to insert into the AVL tree.
* `Delete a word from the AVL tree`: Prompts the user to enter a word to delete from the AVL tree.
* `Print the words as sorted in the AVL tree`: Prints the words and their frequencies in sorted order.
* `Create the hash table`: Initializes the hash table.
* `Insert all words from AVL tree to the hash table`: Inserts all words from the AVL tree into the hash table.
* `Insert a word from AVL tree to the hash table`: Prompts the user to enter a word to insert into the hash table.
* `Delete a word from the hash table`: Prompts the user to enter a word to delete from the hash table.
* `Search for a word in the hash table`: Prompts the user to enter a word to search for in the hash table.
* `Print word statistics`: Prints statistics about the words in the hash table.
* `Exit the application`: Frees memory and exits the program.

## Notes
* Ensure the input file input.txt is present in the parent directory before running the program.
* Words longer than 5 characters will cause errors due to the fixed-size word buffer.

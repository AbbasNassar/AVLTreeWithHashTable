/* Abbas Nassar 1210482 Sec.3 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* General notes about this project:
 * The delete function related to the AVL tree deletes a node without re-balancing.
 * If the word to be deleted from the tree has more than one frequency, the frequency is decremented until it reaches one, then the node is deleted.
 * Words more than 5 digits can cause integer overflow Causing the index to be negative :(.
 * For the hashing table, collisions are handled by Quadratic handling.
 * Re-hashing is not implemented in this code :(.
 * */
int hashTableSize = 47;// prime number.

typedef struct AVLNode* AVLPtr;
typedef struct hashNode* hashPtr;
                             

struct AVLNode
{
    char word[5];
    int frequency;
    AVLPtr Left;
    AVLPtr Right;
    int heightOfTree;
};

struct hashNode {
    int frequency;
    char key[5];
};

AVLPtr makeEmpty(AVLPtr tree);// This function is used to free the memory allocated for the AVL tree.
AVLPtr findNode(char word[], AVLPtr tree);// This function is used to find a specific node, return null if not found.
AVLPtr findMinNode( AVLPtr tree );// This function is used to find the minimum node of branch, used for delete function .
int heightOfTree( AVLPtr subtree );// This function is used to find the height of a specific branch in the tree, used in balancing the tree.
int maxOfHeights(int leftBranch, int rightBranch);// This function is used to find the maximum height of the left and the right branches, used in rotation functions.
AVLPtr singleRotateWithLeft( AVLPtr subTree );
AVLPtr singleRotateWithRight( AVLPtr subTree );
AVLPtr doubleRotateWithLeft( AVLPtr subTree );
AVLPtr doubleRotateWithRight( AVLPtr subTree );
AVLPtr insertNode( char word[] , AVLPtr T );
void printTree( AVLPtr t);// This function is used to print the words and frequencies of each node in the tree (in-order).
AVLPtr  deleteNode ( char word[], AVLPtr t );// This function deletes a node from the tree.
                                            // If the node has no children, deletes it and return the updated tree.
                                            // If the node has one child it replaces the node with its child (make it the new root) then deletes the wanted node.
                                            // If the node has two children, the new root becomes the smallest node in the right subtree.

hashPtr createHashNode(AVLPtr tree);// This function is used to take a tree node and copy its data(word and frequency) and return the pointer for that data.
int stringHashing (char key[], int tableSize, int i);// This function is used to hash an input string.
                                                    // It takes the key and the table size and a counter i as inputs.
                                                    // Counter i is used as a counter for Quadratic handling.
                                                    // It returns the index where the word must be stored in the array.
void hashWord (AVLPtr node, hashPtr hashTable[]);// This function is used to insert a word in the right place in hashTable.
                                              // It takes a node from the tree and the hash table as inputs.
                                              // then initializes the counter i (used in quadratic handling).
                                              // then get the index where to store the word from stringHashing function.
                                              // if this place is free, insert word to it.
                                              // if occupied, loop through the elements of the hashTable incrementing i and updating the index to store until the place is free.
                                              // if the index is more than the hash table size print a message and stop the function.
void traverseHashing(AVLPtr tree, hashPtr hashTable[]);// Same as the above function, but it stores all the words in the tree.
hashPtr searchHashTable(AVLPtr tree, hashPtr hashTable[]);// This function searches for a specific node in the hash table, return null if not found.
void deleteHashTable(AVLPtr tree, hashPtr hashTable[]);// This function deletes a specific node in the hash table, print a message in the hash table.
int main(){
    /* Initializes the needed pointers */
    AVLPtr tree ;
    hashPtr hashTable[hashTableSize];

    /* Menu */
    int selection = 0;
    do
    {
        printf("1- Load data from the file.\n");
        printf("2- Create the AVL tree.\n");
        printf("3- insertNode a word to the AVL tree.\n");
        printf("4- Delete a word from the AVL tree.\n");
        printf("5- Print the words as sorted in the AVL tree.\n");
        printf("6- Create the hash table.\n");
        printf("7- insertNode all the words from AVL tree to the Hash table.\n");
        printf("8- insertNode a word from AVL tree to the Hash table.\n");
        printf("9- Delete a word from the hash table.\n");
        printf("10- Search for a word in the hash table.\n");
        printf("11- Print words statistics.\n");
        printf("12- Exit the application.\n");
        scanf("%d", &selection);
        if (selection == 1)
        {
            char line[7]; // Word for each line (Maximum 5 characters) + new line + null terminator.
            /* Read string from file */
            FILE *file = fopen("../input.txt", "r");
            if (file == NULL)
            {
                printf("Error finding the file :(\n");
            }
            /* Read all the lines until the end is reached */
            while (fgets(line, sizeof(line), file) != NULL)
            {
                line[strlen(line)-1] = '\0';// To remove \n from words
                printf("word: %s\n", line);
            }
            printf("\n");
            /* Close file */
            fclose(file);
            printf("Data is loaded successfully from the file\n");
        }
        else if (selection == 2)
        {
            tree = makeEmpty(tree);
            char line[7];
            /* Read string from file */
            FILE *file = fopen("../input.txt", "r");
            /* Read all the lines until the end is reached */
            while (fgets(line, sizeof(line), file) != NULL)
            {
                line[strlen(line)-1] = '\0';// To remove \n from words
                tree = insertNode(line, tree);
            }
            printf("\n");
            /* Close file */
            fclose(file);
          printf("AVL tree is created :)\n");
        }
        else if (selection == 3)
        {
            char insertedWord[20];
            printf("Enter the word you want to insertNode to the AVL tree:");
            getchar();
            gets(insertedWord);
            tree = insertNode(insertedWord, tree);
            printf("Word inserted successfully :)\n");
        }
        else if (selection == 4)
        {
            char insertedWord[20];
            printf("Enter the word you want to delete from the AVL tree:\n");
            getchar();
            gets(insertedWord);
            tree = deleteNode(insertedWord, tree);
        }
        else if (selection == 5)
        {
            printTree(tree);
        }
        else if (selection == 6)
        {
            for (int i=0; i<hashTableSize; i++){
             hashTable[i] = NULL;// Initialization
           }
           printf("Hash table has been created :)\n");
        }
        else if (selection == 7) {
            traverseHashing(tree, hashTable);
        }
        else if (selection == 8)
        {
            char insertedWord[5];
            printf("Enter the word you want to enter to the hash table:\n");
            getchar();
            gets(insertedWord);
            AVLPtr wantedNode = findNode(insertedWord, tree);
            if (wantedNode == NULL)
                printf("Word is not in the tree :(\n");
            else{
                hashWord(wantedNode, hashTable);
            }
        }
        else if (selection == 9)
        {
            char insertedWord[5];
            printf("Enter the word you want to delete from the hash table:\n");
            getchar();
            gets(insertedWord);
            AVLPtr temp = findNode(insertedWord, tree);
            if (temp == NULL)
                printf("word is not in the AVL tree :(\n");
            else{
                deleteHashTable(temp, hashTable);
            }
        }
        else if (selection == 10){
            char insertedWord[5];
            printf("Enter the word you want to print its frequency from the hash table:\n");
            getchar();
            gets(insertedWord);
            AVLPtr temp = findNode(insertedWord, tree);
            if (temp == NULL)
                printf("word is not in the AVL tree :(\n");
            else{
                hashPtr hashNode = searchHashTable(temp, hashTable);
                if (hashNode == NULL)
                    printf("Word is not in the hash table :(\n");
                else
                    printf("%s frequency is: %d\n", hashNode->key, hashNode->frequency);
            }
        }
        else if (selection == 11){
            int totalNOU=0, threshold;
            printf("First enter frequency threshold value:");
            scanf("%d", &threshold);
            hashPtr mostFreq =(hashPtr) malloc(sizeof(struct hashNode));
            mostFreq->frequency = 1;
            for (int i=0; i<hashTableSize; i++){
                if(hashTable[i] != NULL){
                    if (hashTable[i]->frequency == 1)
                        totalNOU++;
                    if (mostFreq->frequency < hashTable[i]->frequency)
                        mostFreq = hashTable[i];
                    if (hashTable[i]->frequency > threshold)
                        printf("%s frequency is more than threshold frequency = %d with frequency = %d\n", hashTable[i]->key, threshold, hashTable[i]->frequency);
                    else
                    printf("word: %s, with frequency: %d\n", hashTable[i]->key,hashTable[i]->frequency);
                }
            }
            printf("The most frequent word in the hash table is: %s, with frequency of %d\n", mostFreq->key, mostFreq->frequency);
            printf("Number of unique words: %d\n", totalNOU);
        }
        else if (selection == 12){
            makeEmpty(tree); // Free memory reserved by tree.
            for (int i=0; i<hashTableSize; i++){// Free memory reserved by the hashTable
                free(hashTable[i]);
            }
            exit(0);
        }
        else
        {
            printf("Invalid selection number. Try again ;)\n");
        }

    } while (1);
}
AVLPtr makeEmpty( AVLPtr tree )
{
    if( tree != NULL )
    {
        makeEmpty( tree->Left );
        makeEmpty( tree->Right );
        free( tree );
    }
    return NULL;
}

AVLPtr findNode( char word[], AVLPtr tree )
{
    if( tree == NULL )
        return NULL;
    if( strcmp(word, tree->word) < 0)
        return findNode( word, tree->Left );
    else if( strcmp(word, tree->word) > 0)
        return findNode( word, tree->Right );
    else
        return tree;
}

AVLPtr findMinNode( AVLPtr T )
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return findMinNode( T->Left );
}
int heightOfTree( AVLPtr subTree )
{
    if( subTree == NULL )
        return -1;
    else
        return subTree->heightOfTree;
}

int maxOfHeights( int leftBranch, int rightBranch )
{
    int result;
    if (leftBranch > rightBranch) {
        result = leftBranch;
    } else {
        result = rightBranch;
    }
    return result;
}

/* This function can be called only if node has a left child */
/* Perform a rotation between the node and its left child */
/* Update heightOfTrees, then return new root */

AVLPtr singleRotateWithLeft( AVLPtr node )
{
    AVLPtr  temp;

    temp = node->Left;
    node->Left = temp->Right;
    temp->Right = node;

    node->heightOfTree = maxOfHeights( heightOfTree( node->Left ), heightOfTree( node->Right ) ) + 1;
    temp->heightOfTree = maxOfHeights( heightOfTree( temp->Left ), node->heightOfTree ) + 1;

    return temp;  /* New root */
}


/* This function can be called only if K1 has a right child */
/* Perform a rotation between a node (K1) and its right child */
/* Update heightOfTrees, then return new root */

AVLPtr singleRotateWithRight( AVLPtr node )
{
    AVLPtr temp;

    temp = node->Right;
    node->Right = temp->Left;
    temp->Left = node;

    node->heightOfTree = maxOfHeights( heightOfTree( node->Left ), heightOfTree( node->Right ) ) + 1;
    temp->heightOfTree = maxOfHeights( heightOfTree( temp->Right ), node->heightOfTree ) + 1;

    return temp;  /* New root */
}

/* This function can be called only if node has a left */
/* child and node's left child has a right child */
/* Do the left-right double rotation */
/* Update heightOfTrees, then return new root */

AVLPtr doubleRotateWithLeft( AVLPtr node )
{
    node->Left = singleRotateWithRight( node->Left );
    return singleRotateWithLeft( node );
}

/* This function can be called only if node has a right */
/* child and node's right child has a left child */
/* Do the right-left double rotation */
/* Update heightOfTrees, then return new root */

AVLPtr doubleRotateWithRight( AVLPtr node )
{
    node->Right = singleRotateWithLeft( node->Right );
    return singleRotateWithRight( node );
}

AVLPtr insertNode( char word[] , AVLPtr T )
{

    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = (AVLPtr)malloc( sizeof( struct AVLNode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy(T->word, word);
            T->frequency = 1;
            T->Left = T->Right = NULL;
        }
    }
    else if(strcmp(word, T->word) < 0)
    {
        T->Left = insertNode( word, T->Left );
        if( heightOfTree( T->Left ) - heightOfTree( T->Right ) == 2 )
            if( strcmp(word, T->Left->word) < 0)
                T = singleRotateWithLeft( T );
            else
                T = doubleRotateWithLeft( T );
    }
    else if( strcmp(word, T->word) > 0)
    {
        T->Right = insertNode( word, T->Right );
        if( heightOfTree( T->Right ) - heightOfTree( T->Left ) == 2 )
            if( strcmp(word, T->Right->word) > 0 )
                T = singleRotateWithRight( T );
            else
                T = doubleRotateWithRight( T );
    }
        /* Else word is in the tree already; we'll do nothing */
    else if(strcmp(word, T->word) == 0)
        T->frequency = T->frequency + 1;
    T->heightOfTree = maxOfHeights( heightOfTree( T->Left ), heightOfTree( T->Right ) ) + 1;
    return T;
}

void printTree( AVLPtr tree)
{
    if( tree != NULL)
    {
        printTree( tree->Left );
        printf("%s, %d\n", tree->word, tree->frequency);
        printTree( tree->Right );
    }
}


AVLPtr  deleteNode ( char word[], AVLPtr tree ) {
    AVLPtr temp;
    if (tree == NULL)
        printf("Element not found :(\n");
    else if (strcmp(word, tree->word) < 0) /* Go left */
        tree->Left = deleteNode(word,tree->Left);
    else if (strcmp(word, tree->word) > 0) /* Go right */
        tree->Right = deleteNode(word, tree->Right);
    else /* Found element to be deleted */
    if (tree->frequency > 1){// Handles if the word already exists
        tree->frequency =tree->frequency - 1;
    }
    else{
        if (tree->Left && tree->Right) {/* Two children */
            /* Replace with smallest in right subtree*/
            temp = findMinNode(tree->Right);
            strcpy(tree->word, temp->word);
            tree->Right = deleteNode(tree->word, tree->Right);
        } else {/* One or zero children */
            temp = tree;
            if (tree->Left == NULL)
                /* Also handles 0 children */
                tree = tree->Right;
            else if (tree->Right == NULL)
                tree = tree->Left;
            free(temp);
            printf("Word deleted successfully :)\n");
        }
    }
    return tree;
}
hashPtr createHashNode(AVLPtr tree){
    hashPtr hashIndex = (hashPtr)malloc(sizeof(struct hashNode));
    if (hashIndex == NULL)
    {
        printf("Could not create hash indices :(\n");
        return NULL;
    }
    else
    {
        hashIndex->frequency = tree->frequency;
        strcpy(hashIndex->key, tree->word);
    }

    return hashIndex;
}
int stringHashing (char key[], int tableSize, int i)
{
    int hashValue = 0;
    while( *key != '\0' ){
        hashValue = ( hashValue << 5 ) + *key++;
    }
    return (hashValue % tableSize) + (i * i);// Quadratic hashing is used.
}
void hashWord (AVLPtr node, hashPtr hashTable[]){
    int i = 0;
    int realIndex = stringHashing(node->word, hashTableSize, i);
    while (hashTable[realIndex] != NULL){// Handle occupied places
        i++;
        realIndex = stringHashing(node->word, hashTableSize, i);// When the loop breaks, the index reached is an empty slot
        if (realIndex > hashTableSize){
            printf("Error: index out of boundaries :(\n");// Rehashing is needed
            return;
        }
    }
    hashTable[realIndex] = createHashNode(node);
    printf("Word %s is hashed successfully", node->word);
}
void traverseHashing(AVLPtr tree, hashPtr hashTable[]){
    if( tree != NULL)
    {
        traverseHashing( tree->Left, hashTable);
        int i = 0;
        int realIndex = stringHashing(tree->word, hashTableSize, i);
        while (hashTable[realIndex] != NULL){// Handle occupied places
            i++;
            realIndex = stringHashing(tree->word, hashTableSize, i);// When the loop breaks, the index reached is an empty slot
            if (realIndex > hashTableSize){
                printf("Error: index out of boundaries :(\n");
                return;
            }
        }
        hashTable[realIndex] = createHashNode(tree);
        printf("Word %s  is hashed successfully\n", tree->word);
        traverseHashing( tree->Right, hashTable);
    }
}
hashPtr searchHashTable(AVLPtr tree, hashPtr hashTable[]){
    int i = 0;
    int realIndex = stringHashing(tree->word, hashTableSize, i);
    if (hashTable[realIndex] == NULL){
        return NULL;
    }
    else if (strcmp(hashTable[realIndex]->key, tree->word) == 0)
        return hashTable[realIndex];
    else{
        while (hashTable[realIndex] != NULL){// Handle occupied places
            i++;
            realIndex = stringHashing(tree->word, hashTableSize, i);// When the loop breaks, the index reached is an empty slot
            if (realIndex > hashTableSize){
                return NULL;
            }
            else if (strcmp(hashTable[realIndex]->key, tree->word) == 0)
                return hashTable[realIndex];
        }
        printf("word is not found in the hash table.\n");
        return NULL;
    }
}
void deleteHashTable(AVLPtr tree, hashPtr hashTable[]){// From hash table
    int i = 0;
    int realIndex = stringHashing(tree->word, hashTableSize, i);
    if (strcmp(hashTable[realIndex]->key, tree->word) == 0){
        printf("Word is deleted successfully\n");
        hashTable[realIndex] = NULL;
    }
    else{
        while (hashTable[realIndex] != NULL){// Handle occupied places
            i++;
            realIndex = stringHashing(tree->word, hashTableSize, i);// When the loop breaks, the index reached is an empty slot
            if (realIndex > hashTableSize){
                printf("Word is not found in the hash table :(\n");
                return;
            }
            else if (strcmp(hashTable[realIndex]->key, tree->word) == 0){
                hashTable[realIndex] = NULL;
                printf("Word is deleted successfully\n");
            }
        }
    }
}
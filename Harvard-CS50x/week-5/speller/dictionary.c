// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Counter for number of words in loaded dictionary
int counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // LENGTH = 45
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5425;

// Hash table
node *table[N]; // an array of node pointers

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash word to obtain hash value
    int index = hash(word);
    // access linked list at that index in the hash table
    node *cursor = table[index];
    // traverse linked list, looking for the word (strcasecmp: compares strings case insensitively)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
// Consider a hash function that uses a sum of ASCII values or the length of a word.
unsigned int hash(const char *word)
{
    // TODO
    int sum = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        sum += tolower(word[i]);
    }
    return sum - 'a';
}

// Loads dictionary into memory (into a hash table), returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("File could not open.\n");
        return false;
    }
    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) !=
           EOF) // fscanf will return EOF once it reaches end of file
                // %s: reads subsequent characters until a whitespace is found
                // whitespace = blank / newline / tab
                // word = character array that you're gonna read the word into
    {
        // Create space for a new hash table node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // copy the word into the new node
        strcpy(n->word, word);
        n->next = NULL;
        // hash the word to obtain its hash value
        int index = hash(word); // returns an index
        // insert the new node into beginning of linked list of the hash table
        n->next = table[index];
        table[index] = n;
        counter++;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) // looping through the linked lists in hash table
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}

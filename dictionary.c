// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (LENGTH + 1) * ('z');

// Hash table
node *table[N];

// Declaring variables to be used
unsigned int word_count = 0;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to obtain a hash value
    hash_value = hash(word);

    // Access linked list at index hashed and traverse linked list looking for the word
    for (node *tmp = table[hash_value]; tmp != NULL; tmp = tmp->next)
    {
        // If word found, return true
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }

    // If word not found, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // Sum the letters of the word
    unsigned int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }

    // Return the sum % N (so the value is not greater than the number of buckets)
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file on reading mode. If NULL, return false.
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Couldn't open file.\n");
        return false;
    }

    // Create string to store each word of dictionary
    char word[LENGTH + 1];

    // Scan strings from file one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word. If NULL, return false
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory to allocate.\n");
            return false;
        }

        // Copy string word into "word" of node n and point "next" to NULL
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to obtain a hash value for the bucket where that word will go in the table
        hash_value = hash(word);

        // Insert node at hash table
        // If there aren't any words at said bucket, just insert it
        if (table[hash_value] == NULL)
        {
            table[hash_value] = n;
        }
        // Else, point new node to node already in the linked list and point head of list to new node
        else
        {
            n->next = table[hash_value];
            table[hash_value] = n;
        }
        //Counting words to use at size function
        word_count++;
    }

    // Close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //Call free on any memory allocated using malloc
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    //Return true if it's able to do it successfully
    return true;
}

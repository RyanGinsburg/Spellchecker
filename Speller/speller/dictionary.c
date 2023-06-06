#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


unsigned int word_count = 0;

#include "dictionary.h"

//node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary
bool check(const char *word)
{
    int value = hash(word);

    node *cursor = table[value];

    //loop through linked list
    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int letter = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        letter = letter + tolower(word[i]);
    }
    return letter % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //if nothing is there
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n -> word, word);
        n -> next = NULL;
        int value = hash(word);

        //if there is no table
        if (table[value] == NULL)
        {
            table[value] = n;
        }
        else
        {
            n -> next = table[value];
            table[value] = n;
        }
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i] ->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
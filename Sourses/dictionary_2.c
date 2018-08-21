/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

typedef union
{
    int LetterNumber;
    char Letter;
} BUFFER;

typedef struct Node
{
    bool is_word;
    struct Node * down[QTYLETTER];
} NODE;

NODE * InitializeTrieDict(int n);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    NODE * ptr_str_TrieDictRoot = InitializeTrieDict(LENGTH + 1);
    NODE * ptr_str_TrieDictTemp = ptr_str_TrieDictRoot;

    FILE * ptr_DictOpen = fopen(dictionary, "r");
    if(ptr_DictOpen == NULL)
    {
        fprintf(stderr, "File \"%s\" does not open\n", dictionary);
        return false;
    }

    /**
     * LetterIndex - номер буквы начиная с 0 и заканчивая 26, где 0 = "a", 1 = "b" и так
     * далее до 25 = "z", а 26 = "'" (апостроф)
     */
    BUFFER uni_Buffer;
    uni_Buffer.LetterNumber = 0;
    int LetterIndex = -1;
    int LetterCounter = 0;
    unsigned int QtyWords = 0;
    while((uni_Buffer.LetterNumber = getc(ptr_DictOpen)) != EOF)
    {
        if(isalpha(uni_Buffer.Letter))
        {
            if(LetterCounter > 44)
            {
                fprintf(stderr, "The word in the dictionary \"%s\" is longer than 45 characters\n", dictionary);
                return false;
            }
            LetterIndex = uni_Buffer.LetterNumber - 97;
            ptr_str_TrieDictTemp = (*ptr_str_TrieDictTemp).down[LetterIndex];
            LetterCounter++;
        }
        else if(uni_Buffer.LetterNumber == '\'')
        {
            if(LetterCounter > 44)
            {
                fprintf(stderr, "The word in the dictionary \"%s\" is longer than 45 characters\n", dictionary);
                return false;
            }
            LetterIndex = 26;
            ptr_str_TrieDictTemp = (*ptr_str_TrieDictTemp).down[LetterIndex];
            LetterCounter++;
        }
        else if(uni_Buffer.LetterNumber == 0)
        {
            (*ptr_str_TrieDictTemp).is_word = true;
            ptr_str_TrieDictTemp = ptr_str_TrieDictRoot;
            LetterCounter = 0;
            QtyWords++;
        }
    }
    fclose(ptr_DictOpen);
    printf("QtyWords = %u", QtyWords);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

NODE * InitializeTrieDict(int n)
{
    if(n < (LENGTH + 1) && n > 0)
    {
        NODE * ptr_str_TrieDictDown = malloc(sizeof(NODE));
        n--;
        (*ptr_str_TrieDictDown).is_word = false;
        for(int a = 0; a < QTYLETTER; a++)
        {
            (*ptr_str_TrieDictDown).down[a] = InitializeTrieDict(n);
        }
        return ptr_str_TrieDictDown;
    }
    else if(n == (LENGTH + 1))
    {
        NODE * ptr_str_TrieDict = malloc(sizeof(NODE));
        n--;
        (*ptr_str_TrieDict).is_word = false;
        for(int i = 0; i < QTYLETTER; i++)
        {
            (*ptr_str_TrieDict).down[i] = InitializeTrieDict(n);
        }
        return ptr_str_TrieDict;
    }
    else if(n == 0)
    {
        return NULL;
    }
}

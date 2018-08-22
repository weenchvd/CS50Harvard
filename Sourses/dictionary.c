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
    char Letter;
    int LetterNumber;
} UNI_CHARBUFFER;

typedef struct Node
{
    bool is_word;
    struct Node * down[QTYLETTER];
} STR_NODE;

unsigned int WordCounter (STR_NODE *);
bool UnloadDict(STR_NODE *);

STR_NODE * ptr_str_TrieDictRoot;
STR_NODE * ptr_str_TrieDictTemp;
UNI_CHARBUFFER uni_Buffer;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    ptr_str_TrieDictTemp = ptr_str_TrieDictRoot;
    for(int i = 0; i <= LENGTH; i++)
    {
        uni_Buffer.LetterNumber = (int) *(word + i);
        if(uni_Buffer.LetterNumber > 64 && uni_Buffer.LetterNumber < 91)
        {
            uni_Buffer.LetterNumber += 32;
        }
        else if(uni_Buffer.Letter == '\'')
        {
            uni_Buffer.LetterNumber += 84; //because (39 + 84) - 97 = 26 (is index "'" in the STR_NODE.down[index])
        }
        else if(uni_Buffer.Letter == '\0')
        {
            if((*ptr_str_TrieDictTemp).is_word == true) return true;
            else return false;
        }

        if((*ptr_str_TrieDictTemp).down[uni_Buffer.LetterNumber - 97] != NULL)
        {
            ptr_str_TrieDictTemp = (*ptr_str_TrieDictTemp).down[uni_Buffer.LetterNumber - 97];
        }
        else return false;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    ptr_str_TrieDictRoot = malloc(sizeof(STR_NODE));
    (*ptr_str_TrieDictRoot).is_word = false;
    for(int i = 0; i < QTYLETTER; i++)
    {
        (*ptr_str_TrieDictRoot).down[i] = NULL;
    }
    ptr_str_TrieDictTemp = ptr_str_TrieDictRoot;

    FILE * ptr_DictOpen = fopen(dictionary, "r");
    if(ptr_DictOpen == NULL)
    {
        fprintf(stderr, "File \"%s\" does not open\n", dictionary);
        return false;
    }

    /**
     * LetterIndex is the letter number from 0 to 26, where 0 = "a", 1 = "b" and so on
     * to 25 = "z", and 26 = "'" (apostrophe)
     */
    uni_Buffer.LetterNumber = 0;
    int LetterIndex = 0;
    int LetterCounter = 0;
    unsigned int QtyWords = 0;

    while((uni_Buffer.LetterNumber = getc(ptr_DictOpen)) != EOF)
    {
        if(isalpha(uni_Buffer.Letter))
        {
            if(LetterCounter >= LENGTH)
            {
                fprintf(stderr, "The word in the dictionary \"%s\" is longer than 45 characters\n", dictionary);
                return false;
            }

            LetterIndex = uni_Buffer.LetterNumber - 97;
            if((*ptr_str_TrieDictTemp).down[LetterIndex] == NULL)
            {
                STR_NODE * ptr_str_TrieDictDown = malloc(sizeof(STR_NODE));
                (*ptr_str_TrieDictDown).is_word = false;
                for(int x = 0; x < QTYLETTER; x++)
                {
                    (*ptr_str_TrieDictDown).down[x] = NULL;
                }
                (*ptr_str_TrieDictTemp).down[LetterIndex] = ptr_str_TrieDictDown;
            }

            ptr_str_TrieDictTemp = (*ptr_str_TrieDictTemp).down[LetterIndex];
            LetterCounter++;
        }
        else if(uni_Buffer.LetterNumber == '\'')
        {
            if(LetterCounter >= LENGTH)
            {
                fprintf(stderr, "The word in the dictionary \"%s\" is longer than 45 characters\n", dictionary);
                return false;
            }

            LetterIndex = 26;
            if((*ptr_str_TrieDictTemp).down[LetterIndex] == NULL)
            {
                STR_NODE * ptr_str_TrieDictDown = malloc(sizeof(STR_NODE));
                (*ptr_str_TrieDictDown).is_word = false;
                for(int x = 0; x < QTYLETTER; x++)
                {
                    (*ptr_str_TrieDictDown).down[x] = NULL;
                }
                (*ptr_str_TrieDictTemp).down[LetterIndex] = ptr_str_TrieDictDown;
            }

            ptr_str_TrieDictTemp = (*ptr_str_TrieDictTemp).down[LetterIndex];
            LetterCounter++;
        }
        else if(uni_Buffer.LetterNumber == '\n')
        {
            (*ptr_str_TrieDictTemp).is_word = true;
            ptr_str_TrieDictTemp = ptr_str_TrieDictRoot;
            LetterCounter = 0;
            QtyWords++;
        }
        else
        {
            fprintf(stderr, "Invalid character in the dictionary \"%s\"\n", dictionary);
            return false;
        }
    }

    fclose(ptr_DictOpen);
    printf("Quantity of words when the dictionary is loaded: %u\n", QtyWords);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return WordCounter(ptr_str_TrieDictRoot);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return UnloadDict(ptr_str_TrieDictRoot);
}

unsigned int WordCounter (STR_NODE * ptr_str_TrieDictDown)
{
    unsigned int QtyWords = 0;
    for(int i = 0; i < QTYLETTER; i++)
    {
        if((*ptr_str_TrieDictDown).down[i] != NULL)
        {
            QtyWords += WordCounter((*ptr_str_TrieDictDown).down[i]);
        }
    }
    if((*ptr_str_TrieDictDown).is_word == true) QtyWords++;
    return QtyWords;
}

bool UnloadDict(STR_NODE * ptr_str_TrieDictDown)
{
    for(int i = 0; i < QTYLETTER; i++)
    {
        if((*ptr_str_TrieDictDown).down[i] != NULL)
        {
            if(!UnloadDict((*ptr_str_TrieDictDown).down[i]))
            {
                return false;
            }
        }
    }
    free(ptr_str_TrieDictDown);
    return true;
}

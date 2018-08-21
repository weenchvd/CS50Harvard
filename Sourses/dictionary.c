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
} UNI_CHARBUFFER;

typedef struct Node
{
    bool is_word;
    struct Node * down[QTYLETTER];
} STR_NODE;

STR_NODE * ptr_str_TrieDictRoot;
UNI_CHARBUFFER uni_Buffer;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char * ptr_CheckWord = (char *) word;
    int LetterCounter = 0;
    for(int i = 0; i <= LENGTH; i++)
    {
        int c = (int) (*(ptr_CheckWord + i));
        if(c > 64 && c < 91)
        {
            uni_Buffer.LetterNumber = (c + 32);
            *(ptr_CheckWord + i) = uni_Buffer.Letter;
        }
        else if(c == '\0')
        {
            break;
        }
        LetterCounter++;
    }

    for(int j = 0; j < LetterCounter; j++)
    {

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
    STR_NODE * ptr_str_TrieDictTemp = ptr_str_TrieDictRoot;

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
    printf("QtyWords = %u\n", QtyWords);
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

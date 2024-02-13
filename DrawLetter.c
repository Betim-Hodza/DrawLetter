// Betim Hodza 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DrawTool.h"
#include "ListLib.h"
#include "FileLib.h"

int main(int argc, char *argv[])
{
    //array map
    char arraysize[MAXMAPSIZE][MAXMAPSIZE] = {}; //CA4 vars
    //file vars
    char DC[50] = {}; 
    FILE *FH = NULL;
    //LinkedList Vars
    char letters[5] = {}; 
    NODE *LinkedListHead = NULL;
    NODE *TempPtr;
    char current_letter = '\0';
    //strok vars
    char *token = NULL;
    char *delimiters = "() ,";
    int from = 0, to = 0, count = 0;
    char linetype[MAXMAPSIZE] = {};
    char mark[MAXMAPSIZE] = {}; 


    FH = OpenFile(argc, argv);
    ReadFileIntoLinkedList(FH, &LinkedListHead);

    InitializeMap(arraysize);

    //asks user for 1-3 letters, and keeps on asking if the user inputs the wrong amt of letters
    printf("\nEnter 1-3 letters: ");
    scanf("%s", letters);
    if (strlen(letters) > 3 || strlen(letters) < 1)
    {
        while ((strlen(letters) > 3 || strlen(letters) < 1))
        {
            printf("invalid number of letters, please enter again: ");
            scanf("%s", letters);
        }
    }

    for(int i = 0; i < strlen(letters); i++) //loop over strlen of numbers of letters entered
    {
        current_letter = toupper(letters[i]); //uppercases letter
        TempPtr = FindLetter(LinkedListHead, current_letter, DC); //starts searching for letter

        while (strlen(DC) != 0)
        {
            //Tokenizes drawcommands
            token = strtok(DC, delimiters);
            strcpy(linetype, token);
            token = strtok(NULL, delimiters);
            from = atoi(token);
            token = strtok(NULL, delimiters);
            to = atoi(token);
            token = strtok(NULL, delimiters);
            count = atoi(token);
            token = strtok(NULL, delimiters);
            strcpy(mark, token); 
            //prints draw command and offsets it if its second or third letter
            if (i == 0)
            {
                DrawLine(arraysize, from, to, *linetype, count, *mark);
            }
            else if(i == 1)
            {
                DrawLine(arraysize, from, to+7, *linetype, count, *mark);
            }
            else if (i == 2)
            {
                DrawLine(arraysize, from, to+14, *linetype, count, *mark);
            }
            //picks up where FindLetter left off by passing &TempPtr
            TempPtr = FindLetter(TempPtr, current_letter, DC);
        }
    }
    PrintMap(arraysize);
    printf("\n");

    fclose(FH); //closed FH we are done with it

    return 0;
}


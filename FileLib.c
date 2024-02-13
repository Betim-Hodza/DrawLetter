/* Betim Hodza FileLib.c */

#include <stdio.h>
#include <string.h>
#include "ListLib.h"

/************************
 * searches for a string
 * in the command line parameter
 * then stores the value of it 
 * into a char array after
*****************************/
void get_command_line_parameter(char *argv[], char PName[], char PValue[])
{
    int i = 1;
    while (argv[i] != NULL)
    {
        if (!strncmp(argv[i], PName, strlen(PName)))
        {
            strcpy(PValue, strchr(argv[i], '=') + 1);
        }
        i++;
    }
}
/************************
 * Passes in argc and argv
 * Opens a file from the 
 * command line and assigns it
 * a variable using 
 * get_command_line_parameter func.
 * it opens it up and returns the file handler.
*****************************/
FILE *OpenFile(int argc, char *argv[])
{	
	FILE *FH = NULL;
	char FILENAME[100] = {};
	//Using advanced command line parameters
	if (argc == 2)
	{
		get_command_line_parameter(argv, "FILENAME=", FILENAME);
	}
	else
	{
		printf("Must be run with an input file name. \nEnter a file name at the prompt: \n"); 
		scanf("%s", FILENAME);
	}
	

	do
	{
		FH = fopen(FILENAME, "r");
		if(FH == NULL) 
		{
			printf("Could not open input file named %s \n\n Enter a file name at the prompt: ", FILENAME); 
			scanf("%s", FILENAME); 
			FH = fopen(FILENAME, "r");
		}
	}
	while (FH == NULL);

	return FH; 
}
/************************
 * takes in draw
 * commands from input.txt,
 * and replaces the newline
 * with the null, then it 
 * tokenizes the letter 
 * of the draw command and
 * the drawcommand itself
 * and then sends both variables
 * to the linked list head.
*****************************/
void ReadFileIntoLinkedList(FILE *DCFile, NODE **LinkedListHead)
{
	char str1[30] = {};
	char *delimiters = "|\0";
	char *Token = NULL;
	char Letter;
	char drawcommand_out[50] = {};

	
	while(fgets(str1, sizeof(str1)-1, DCFile)) //fgets reads file
	{
		if(str1[strlen(str1) - 1] == '\n') //if the line ends with \n
		{
			str1[strlen(str1) - 1] = '\0'; //replace with \0
		}
		/* tokenize to get the Letter and the DrawCommand */
    	Token = strtok(str1, delimiters);
		Letter = *Token;
		Token = strtok(NULL, delimiters);
		strcpy(drawcommand_out, Token);
    	//stores letter and draw command in linked list
		AddDrawCommandToList(Letter, drawcommand_out, LinkedListHead); 
	}
}

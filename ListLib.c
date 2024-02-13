/* Betim Hodza ListLib.c */

#include "ListLib.h"
/**********************
 * adds drawcommand
 * to the end of the 
 * linked list
***********************/
void AddDrawCommandToList(char letter, char drawcommand_out[], NODE **LinkedListHead)
{
    NODE *TempPtr, *NewNode;
	//allocates space for NewNode
	NewNode = malloc(sizeof(NewNode));
	NewNode->Letter = letter;
	//allocates space for the drawcommand inside of the node, since its unknown how big it will be
	NewNode->DrawCommand = malloc(strlen(drawcommand_out) + 1); 
	strcpy(NewNode->DrawCommand, drawcommand_out); //stores drawcommand in node
	NewNode->next_ptr = NULL;

	if (*LinkedListHead == NULL) 
	{
		*LinkedListHead = NewNode;
	}
	else
	{
		TempPtr = *LinkedListHead;
		while(TempPtr->next_ptr != NULL) //stops at last node
		{
    		TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode; //adds new node to the last one
	}
}

/**********************
 * Searches for char
 * Letter inside of
 * linked list
***********************/
NODE *FindLetter(NODE *LinkedListHead, char Letter, char DC[])
{
	NODE *TempPtr = LinkedListHead;
	while(TempPtr != NULL && TempPtr->Letter != Letter) //looks for Letter passed in, inside linked list
	{
		TempPtr = TempPtr->next_ptr;
	}
	// when it finds it, and temp ptr isnt null, it copies it into the passed in array
	if (TempPtr != NULL) 
	{
		strcpy(DC, TempPtr->DrawCommand); 
		return TempPtr->next_ptr; 
	}
	else //if it doesnt find it, it flags DC to null to stop looking
	{
		memset(DC, '\0', sizeof(*DC));  
		return TempPtr; 
	}
}

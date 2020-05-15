/*

  File: voter.c

  Abstract:

    Voter handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "voter.h"


/*
 * Types
 */
typedef struct _Voter
{
    char* pName;
    char* pParty;
    int ID;

    struct _Voter* pNext;
} Voter;


/*
 * Statics
 */
static Voter* VoterList = NULL;


/*

  Function: AddVoter

  Abstract:

    Adds a new voter to the database

  Parameters:

    pName    - The voter's name
    pSurname - The voter's surname
    ID		 - The voter's ID (assumed to be unique)
    pParty   - The voter's vote (assumed NOT to be changed)

  Returns: --

*/
void AddVoter(char* pName, char* pSurname, int ID, char* pParty)
{
    /*
     * check for NULL in name because strlen doesn't
     */
    /*if (!(*pName)) {
        *pName = (char*)"";
    }
    if (!(*pSurname)) {
        *pSurname = (char*)"";
    }*/
    /*
     * allocate memory on heap for voter name
     */
    char* fullName = (char*)malloc((strlen(pName) + strlen(pSurname) + 2) * sizeof(char));
    if(fullName == NULL);
    {
        exit(-1);
    }
    strcpy(fullName, pName);
    strcat(fullName, " ");
    strcat(fullName, pSurname);
    /* 
     * make voter name upper case
     */
    char* curr_chr = fullName;
    while (*curr_chr)
    {
        *curr_chr = toupper(*curr_chr);
        curr_chr++;
    }
    /*
     * creat new voter struct on heap with the info given
     */
    Voter* new_voter = (Voter*)malloc(sizeof(Voter));
    if (new_voter == NULL)
    {
        free(fullName);
        exit(-1);
    }
    new_voter->ID = ID;
    new_voter->pName = fullName;
    new_voter->pParty = pParty;
    /*
     * find the place in the voter list to enter the new voter by ID so it is sorted from low to high
     */
    Voter* curr_voter = VoterList;
    while (curr_voter->ID < ID)
        curr_voter++;
    curr_voter--;
    /*
     * enter voter in to voter list in the correct locaation to keep list sorted
     */
    new_voter->pNext = curr_voter->pNext;
    curr_voter->pNext = new_voter;
}


/*

  Function: FreeVoters

  Abstract:

    Frees all memory in the voter data-base

*/
void FreeVoters()
{
    while (VoterList != NULL)
    {
        free(VoterList->pName);
        Voter* tmp = VoterList;
        VoterList = VoterList->pNext;
        free(tmp);
    }
}


/*

  Function: PrintVoters

  Abstract:

    Prints all registered voters

*/
void PrintVoters()
{
    Voter* pVoter;

    printf("Registered Voters\n");
    printf("ID | Name | Vote\n");

    /*
     * Iterate the voter list and print the details of each voter
     */
    for (pVoter = VoterList; pVoter; pVoter = pVoter->pNext)
    {
        printf("%d %s %s\n", pVoter->ID, pVoter->pName, pVoter->pParty);
    }
    printf("\n");
}

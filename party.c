/*

  File: party.c

  Abstract:

    Party handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "party.h"

#define MAX_PARTY_NAME      20

/*
 * Types
 */
typedef struct _Party
{
    char Party_name[MAX_PARTY_NAME];
    int NumVoters;

    struct _Party* pNext;
} Party;


/*
 * Prototypes
 */
void PrintError(char* pPartyName);


/*
 * Statics
 */
static Party* party_list_hd = NULL;
static Party* new_party = NULL;
static Party* curr_party = NULL;


/*

  Function: AddVote

  Abstract:

    Records the chosen party of a voter

  Parameters:

    pPartyName - The party that received the vote

  Returns: A pointer to the party name that is guaranteed to stay constant until 'FreeParties'
           is called. If the party name is illegal, we fail the operation and return NULL.

*/
char* AddVote(char* pPartyName)
{
    char ch = '-';
    char* ret = pPartyName;
    while (ret <= pPartyName + strlen(pPartyName) - 1 && ret) {
        ret = strchr(ret, ch);
        if (ret && (ret != pPartyName + strlen(pPartyName) - 1 || ((ret[1] < 'A') && (ret[1] > 'Z')))) {
            PrintError(pPartyName);
            return NULL;
        }
    }
    /*ret = strchr(pPartyName, ch);

    // checking correctness of party name
    if (((ret[0] == '-') && (ret[1] < 'A') && (ret[1] > 'Z')))
    {
        PrintError(pPartyName);
        return NULL;
    }*/
    curr_party = party_list_hd;
    while (curr_party != NULL)
    {
        
        // if the party already exists
        if (!strcmp(pPartyName, curr_party->Party_name))
        {
            (curr_party->NumVoters)++;
            return curr_party->Party_name;
        }
        else
        {
            curr_party = curr_party->pNext;
        }
    }
    //the party doesn't exist
    new_party = (Party*)malloc(sizeof(Party));
    if (new_party == NULL)
        return NULL; //exit(-1);
    strcpy(new_party->Party_name, pPartyName);
    new_party->NumVoters = 1;
    new_party->pNext = party_list_hd;
    party_list_hd = new_party;
    return new_party->Party_name;
}


/*

  Function: FreeParties

  Abstract:

    Frees all memory in the party database

*/
void FreeParties()
{
    curr_party = party_list_hd;
    while (curr_party != NULL)
    {
        party_list_hd = curr_party->pNext;
        free(curr_party);
        curr_party = party_list_hd;
    }
}


/*

  Function: PrintResult

  Abstract:

    Reports the election result so far

*/
void PrintResult()
{
    Party* pParty;

    printf("Election Results\n");
    printf("Party | Num. of Voters\n");

    /*
     * Iterate the party list and print the current number of voters for each party
     */
    for (pParty = party_list_hd; pParty; pParty = pParty->pNext)
        printf("%s %d\n", pParty->Party_name, pParty->NumVoters);
    printf("\n");
}


void PrintError(char* pPartyName)
{
    printf("ERROR: '%s' is invalid\n", pPartyName);
}
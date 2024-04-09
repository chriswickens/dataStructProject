#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define MAX_STRING_SIZE 151
#define MAX_NUM_PLAYERS 4


// Setup for data structures
typedef struct PlayerTurnList
{
	int playerRotationNumber;
	char playerName[MAX_STRING_SIZE];
	struct Node* NextNode;
} PlayerTurnList;

PlayerTurnList* CreateNewNode(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE])
{
	PlayerTurnList* newPlayerNode = (PlayerTurnList*)malloc(sizeof(PlayerTurnList));
	if (newPlayerNode == NULL)
	{
		printf("No Memory");
		exit(EXIT_FAILURE);
	}

	newPlayerNode->playerRotationNumber = newPlayerRotationNumber;
	strcpy(newPlayerNode->playerName, playerName);
	newPlayerNode->NextNode = NULL;
	return newPlayerNode;
}

void InsertNewNodeAtTheBeginning(int nodeId, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail)
{
	PlayerTurnList* newNode = CreateNewNode(nodeId, playerName); // Make a new node

	if (*head == NULL) // Is the head null?
	{
		newNode->NextNode = newNode;
		*head = newNode;
		*tail = newNode;
		return;
	}

	newNode->NextNode = *head;
	*head = newNode;
	(*tail)->NextNode = *head;
}

void PrintList(PlayerTurnList* head)
{
	if (head == NULL) // Its empty if the head is null
	{
		printf("list is empty, can't do anything\n");
		return;
	}

	PlayerTurnList* current = head;

	do
	{
		printf("Current Player: %s, rotation Number: %d\n", current->playerName, current->playerRotationNumber);
		current = current->NextNode;
	} while (current != head);

}


int getIntFromUser(void);
void clearCarriageReturn(char buffer[]);

void setupPlayerNames(char nameArray[][MAX_STRING_SIZE], int playerCount);

int main(void)
{
	char playerNames[MAX_NUM_PLAYERS][MAX_STRING_SIZE] =
	{
	"Player One",
	"Player Two",
	"Player Three",
	"Player Four"
	};

	PlayerTurnList* head = NULL;
	PlayerTurnList* tail = NULL;

	//char playerOneName[MAX_STRING_SIZE] = { "Player One" };
	//char playerTwoeName[MAX_STRING_SIZE] = { "Player Two" };
	//char playerThreeName[MAX_STRING_SIZE] = { "Player Three" };
	//char playerFourName[MAX_STRING_SIZE] = { "Player Four" };

	// Game starts, determine how many player there are
	printf("How many players would you like for this game? (2-4 players)\n");
	int numberOfPlayers = 0;
	while (numberOfPlayers < 2 || numberOfPlayers > 4)
	{
		numberOfPlayers = getIntFromUser();
		if (numberOfPlayers < 2 || numberOfPlayers > 4)
		{
			printf("Invalid number of players!\n");
		}

		//else
		//{
		//	printf("Number of players set to: %d", numberOfPlayers);
		//}
	}

	// Setup the player rotation in the circular linked list
	switch (numberOfPlayers)
	{
	case 2:
		printf("Setting up game for 2 players!\n");
		setupPlayerNames(playerNames, numberOfPlayers);

		for (int i = 0; i < numberOfPlayers; i++)
		{
			InsertNewNodeAtTheBeginning(i, playerNames[i], &head, &tail);
		}
		break;
	case 3:
		printf("Setting up game for 3 players!\n");
		setupPlayerNames(playerNames, numberOfPlayers);
		break;
	case 4:
		printf("Setting up game for 4 players!\n");
		setupPlayerNames(playerNames, numberOfPlayers);
		break;
	default:
		break;
	}

	// Uncomment to check names
	//for (int i = 0; i < numberOfPlayers; i++)
	//{
	//	printf("Name %d: %s\n", i, playerNames[i]);
	//}
	
	PrintList(head);

	return 0;
}

int getIntFromUser(void)
{
	char userInput[MAX_STRING_SIZE] = { "\0" };
	int inputAsInt = 0;
	fgets(userInput, MAX_STRING_SIZE, stdin);

	while (sscanf(userInput, "%i", &inputAsInt) != 1)
	{
		printf("Invalid entry, try again: ");
		fgets(userInput, MAX_STRING_SIZE, stdin);
	}

	return inputAsInt;
}

void clearCarriageReturn(char buffer[])
{
	char* whereCR = strchr(buffer, '\n');
	if (whereCR != NULL)
	{
		*whereCR = '\0';
	}
}


void setupPlayerNames(char nameArray[][MAX_STRING_SIZE], int playerCount)
{
	int realPlayerCount = 1;

	for (int i = 0; i < playerCount; i++)
	{
		printf("Count: %d\n", realPlayerCount);
		printf("Enter player %d name: \n", realPlayerCount);

		char userInput[MAX_STRING_SIZE] = { "\0" };
		char userName[MAX_STRING_SIZE] = { "\0" };

		fgets(userInput, MAX_STRING_SIZE, stdin);

		while (sscanf(userInput, "%s", &nameArray[i]) != 1)
		{
			printf("Invalid entry, try again: ");
			fgets(userInput, MAX_STRING_SIZE, stdin);
		}

		clearCarriageReturn(nameArray[i]);

		//clearCarriageReturn(userName);
		
		//strcpy(nameArray[i], userName);

		//printf("NAME in ARRAY: %s\n", nameArray[i]);

		realPlayerCount++;
	}
}

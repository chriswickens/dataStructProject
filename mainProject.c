#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define MAX_STRING_SIZE 151
#define MAX_NUM_PLAYERS 4
#define MAX_STACK_SIZE 10


// Setup for data structures

/*
* 
* 
* REMINDERS
* SETUP PROTOTYPES FOR EVERY FUNCTION!
* 
* MAKE SURE YOU FREE MEMORY AFTER THE PROJECT IS DONE!!!!!
* 
* 
*/

// Player Turn List
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


// Player Turn List
void InsertNewNodeAtTheEnd(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail) // Insert a new head
{
	PlayerTurnList* newNode = CreateNewNode(newPlayerRotationNumber, playerName); // New node!

	if (*head == NULL) // Head null, all empty, new node is both head and tail!
	{
		newNode->NextNode = newNode;
		*head = newNode;
		*tail = newNode;
		return;
	}

	(*tail)->NextNode = newNode; // The tail needs to point to the new node since it will be the new head
	newNode->NextNode = *head; // The newnode is the new tail, tell it to go back to the head since it was created null
	*tail = newNode; // The tail can now be the new node
}


void insertNewPlayerTurnNodeBeginning(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail)
{
	PlayerTurnList* newNode = CreateNewNode(newPlayerRotationNumber, playerName); // Make a new node

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

// Player Turn List
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


// Player rolls stacks
typedef struct PlayerRolls
{
	int* rolls;
	int topIndex;
} PlayerRolls;

PlayerRolls* initializePlayerRolls(void)
{
	// Allocate memory for the stack variable
	PlayerRolls* stack = (PlayerRolls*)malloc(sizeof(PlayerRolls));
	if (stack == NULL)
	{
		printf("No memory to initialize stack, exiting.");
		exit(EXIT_FAILURE);
	}

	// allocate memory for the integer array
	stack->rolls = (int*)malloc(sizeof(int) * MAX_STACK_SIZE);

	if (stack->rolls == NULL)
	{
		printf("No memory to initialize stack data member, exiting.");
		exit(EXIT_FAILURE);
	}

	// This sets the topIndex (the last item) to -1 
	// Defaults to -1 to show the stack is EMPTY, since topIndex 0 would mean there is something at 0
	// In the array of ints

	// Create a function that will generate random numbers for the stack rolls



	stack->topIndex = -1;
	return stack;
}

void randomTesting(int numbers[])
{
	srand(time(NULL)); // Seed the random number generator with current time

	int generatedNumbers[10]; // Array to store the generated numbers

	// Generate and store 10 random numbers between 1 and 4
	for (int i = 0; i < 10; ++i)
	{
		numbers[i] = rand() % 10 + 1; // Generate a random number between 1 and 4
	}

	// Print the generated numbers
	printf("Generated numbers:\n");
	for (int i = 0; i < 10; ++i)
	{
		printf("%d\n", generatedNumbers[i]);
	}
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

	// Player turns:
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


	printf("Setting up game for %d players!\n", numberOfPlayers);
	setupPlayerNames(playerNames, numberOfPlayers);

	for (int i = 0; i < numberOfPlayers; i++)
	{
		InsertNewNodeAtTheEnd(i, playerNames[i], &head, &tail);
	}

	
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
	int realPlayerCount = 1; // Not needed (used for printout debugging)

	for (int i = 0; i < playerCount; i++)
	{
		//printf("Count: %d\n", realPlayerCount);
		printf("Enter player %d name: \n", realPlayerCount);

		char userInput[MAX_STRING_SIZE] = { "\0" };
		char userName[MAX_STRING_SIZE] = { "\0" };

		printf("Enter the URL of the web page (max %i characters): ", MAX_STRING_SIZE - 1);
		fgets(userName, MAX_STRING_SIZE, stdin);
		clearCarriageReturn(userName);
		while (userName[0] == '\n' || userName[0] == '\0' || userName[0] == ' ')
		{
			printf("Must be a valid URL (max %i characters): ", MAX_STRING_SIZE - 1);
			fgets(userName, MAX_STRING_SIZE, stdin);
		}
		
		strcpy(nameArray[i], userName);


		realPlayerCount++; // Not needed
	}
}

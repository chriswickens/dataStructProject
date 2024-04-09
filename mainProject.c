#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma warning(disable:4996)

#define MAX_STRING_SIZE 151
#define MAX_NUM_PLAYERS 4
#define MAX_STACK_SIZE 10
#define NUMBER_OF_ROUNDS 10


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

// Player Turn List (circular array)
typedef struct PlayerTurnList
{
	int playerRotationNumber;
	char playerName[MAX_STRING_SIZE];
	struct PlayerRolls* generatedRolls;
	struct Node* NextNode;
} PlayerTurnList;


// Player rolls stacks (stack)
// Each stack created just contains the rolls for the player
typedef struct PlayerRolls
{
	int* rolls;
	int topIndex;
} PlayerRolls;


PlayerRolls* initializePlayerRolls(void);
PlayerTurnList* CreateNewNode(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE]);

void InsertNewPlayerAtEnd(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail);
void PrintList(PlayerTurnList* head);
void Push(PlayerRolls* stack, int elementToAdd);
void printStack(PlayerRolls* stack);
bool isStackEmpty(PlayerRolls* stack);
bool isStackFull(PlayerRolls* stack);

int getIntFromUser(void);
void clearCarriageReturn(char buffer[]);
void setupPlayerNames(char nameArray[][MAX_STRING_SIZE], int playerCount);


int randomNumberGenerator();

void PushTheRolls(PlayerRolls* stack);


int main(void)
{
	srand(time(NULL)); // seed for random numbers

	//printf("\n\nTESING\n\n");
	//for (int i = 0; i < 10; i++)
	//{
	//	printf("Random: %d\n", randomNumberGenerator());
	//}

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


	// TESTING OUT THE PLAYER ROLLS STACK
	// 
	// 


	//PlayerRolls* rollStack = initializePlayerRolls();
	//Push(rollStack);
	//printStack(rollStack);



	//PlayerRolls* playerOneRolls = initializePlayerRolls();
	//PushTheRolls(playerOneRolls);
	//printStack(playerOneRolls);

	//PlayerRolls* playerTwoRolls = initializePlayerRolls();
	//Push(playerTwoRolls);
	//PlayerRolls* playerThreeRolls = initializePlayerRolls();
	//Push(playerThreeRolls);
	//PlayerRolls* playerFourRolls = initializePlayerRolls();
	//Push(playerFourRolls);
	//printStack(playerOneRolls);
	//printStack(playerTwoRolls);
	//printStack(playerThreeRolls);
	//printStack(playerFourRolls);

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

	// Get player names
	setupPlayerNames(playerNames, numberOfPlayers);




	// Insert the players into the circular list and assign rolls
	// break out into function later
	//for (int i = 0; i < numberOfPlayers; i++)
	//{
	//	// Create a new PlayerRolls stack and push rolls onto it
	//	PlayerRolls* playerRolls = initializePlayerRolls();
	//	PushTheRolls(playerRolls);

	//	// Create a new PlayerTurnList node and assign the player's stack
	//	PlayerTurnList* playerNode = CreateNewNode(i, playerNames[i]);
	//	playerNode->generatedRolls = playerRolls;

	//	// Insert the player into the circular list
	//	InsertNewPlayerAtEnd(i, playerNames[i], &head, &tail);
	//}



	//// Print out the circular list and each player's rolls
	//PlayerTurnList* current = head;
	//do
	//{
	//	printf("Player: %s\n", current->playerName);
	//	printStack(current->generatedRolls);
	//	current = current->NextNode;
	//} while (current != head);


	//Insert the players into the circular list
	for (int i = 0; i < numberOfPlayers; i++)
	{
		InsertNewPlayerAtEnd(i, playerNames[i], &head, &tail);
	}



	// Generation testing!

	PlayerTurnList* thisCurrent = head;

	do
	{
		printf("Generating rolls for %s: ", thisCurrent->playerName);
		thisCurrent->generatedRolls = initializePlayerRolls();
		PushTheRolls(thisCurrent->generatedRolls);
		thisCurrent = thisCurrent->NextNode;
	} while (thisCurrent != head);

	//head->generatedRolls = initializePlayerRolls();
	//PushTheRolls(head->generatedRolls);
	PrintList(head);
	//printStack(head->generatedRolls);

	return 0;
}



void PushTheRolls(PlayerRolls* stack)
{
	if (isStackFull(stack))
	{
		printf("!!!!! PUSHTHEROLLS() ERROR, STACK IS FULL\n");
		return;
	}

	for (int i = 0; i < MAX_STACK_SIZE; i++)
	{
		Push(stack, randomNumberGenerator());
	}
}


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
void InsertNewPlayerAtEnd(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail) // Insert a new head
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
		printStack(current->generatedRolls);
		current = current->NextNode;
	} while (current != head);

}


PlayerRolls* initializePlayerRolls(void) // (Stack)
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

	//for (int i = 0; i < MAX_STACK_SIZE; i++)
	//{
	//	stack->rolls[i] = rand() % 10 + 1;
	//}
		// Generate and store 10 random numbers in the rolls array
	//for (int i = 0; i < MAX_STACK_SIZE; i++)
	//{
	//	stack->rolls[i] = randomNumberGenerator();
	//}
	stack->topIndex = -1;
	return stack;
}

void Push(PlayerRolls* stack, int elementToAdd)
{
	if (isStackFull(stack))
	{
		printf("Stack Overflow Exception");
		exit(EXIT_FAILURE);
	}

	//for (int i = 0; i < MAX_STACK_SIZE; i++)
	//{
	//int thisRandomNumber = rand() % 10 + 1;


	stack->rolls[++stack->topIndex] = elementToAdd;
	//}
	//int thisRandomNumber = rand() % 10 + 1;


	//stack->rolls[++stack->topIndex] = thisRandomNumber;
}

void printStack(PlayerRolls* stack)
{
	if (isStackEmpty(stack))
	{
		printf("Stack is empty...\n");
	}

	else
	{
		printf("---PrintOut:---\n");
		int stackTop = stack->topIndex;

		while (stackTop >= 0)
		{
			//int index = stack->topIndex;
			printf("Stack element :  %i Index: %-8i \n", stack->rolls[stackTop], stackTop);
			stackTop--;

		}
		printf("---End of PrintOut---\n\n");
	}

}

bool isStackEmpty(PlayerRolls* stack)
{
	return stack->topIndex == -1;
}

bool isStackFull(PlayerRolls* stack)
{
	return stack->topIndex == MAX_STACK_SIZE - 1;
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

int randomNumberGenerator()
{
	//srand(time(NULL)); // Seed the random number generator with current time

	// Generate and store 10 random numbers between 1 and 4

	return rand() % 10 + 1; // Generate a random number between 1 and 4

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
		printf("Enter player %d name (max %i characters): \n", realPlayerCount, MAX_STRING_SIZE - 1);

		char userInput[MAX_STRING_SIZE] = { "\0" };
		char userName[MAX_STRING_SIZE] = { "\0" };

		//printf("Enter the URL of the web page (max %i characters): ", MAX_STRING_SIZE - 1);
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

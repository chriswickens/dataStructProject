#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma warning(disable:4996)

#define MAX_STRING_SIZE 151
#define MAX_NUM_PLAYERS 4
#define MAX_STACK_SIZE 10
#define NUMBER_OF_ROUNDS 10
#define HASH_TABLE_SIZE 20


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
	struct PlayerTurnList* NextNode;
} PlayerTurnList;

typedef struct GameResults // Used for storing the game results
{
	int score;
	char playerName[MAX_STRING_SIZE];
} GameResults;


// Player rolls stacks (stack)
// Each stack created just contains the rolls for the player
typedef struct PlayerRolls
{
	int* rolls;
	int topIndex;
} PlayerRolls;


// Hash table structs
typedef struct KeyValuePair // The main key/value pair
{
	char* key;
	char* value;
	struct KeyValuePair* NextKeyValuePair;
} KeyValuePair;

typedef struct HashTable // The hash TABLE where key/value pairs are stored (array of KeyValuePair)
{
	KeyValuePair* Table[HASH_TABLE_SIZE];
} HashTable;


PlayerRolls* initializePlayerRolls(void);
PlayerTurnList* CreateNewNode(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE]);

void InsertNewPlayerAtEnd(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail);
void PrintList(PlayerTurnList* head);
void Push(PlayerRolls* stack, int elementToAdd);

int pop(PlayerRolls* stack);
int peek(PlayerRolls* stack);

void printStack(PlayerRolls* stack);
bool isStackEmpty(PlayerRolls* stack);
bool isStackFull(PlayerRolls* stack);

int getIntFromUser(void);
void clearCarriageReturn(char buffer[]);
void setupPlayerNames(char nameArray[][MAX_STRING_SIZE], int playerCount);


int randomNumberGenerator();

void PushTheRolls(PlayerRolls* stack);

void InsertNewPlayerSorted(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail);


// HASH specific
int GenerateHash(char* word);
KeyValuePair* InitializeKeyValuePair(char* key, char* value);
HashTable* InitializeHashTable(void);
char* SearchHashTable(HashTable* hashTable, char* keyToFind);
void InsertSeparateChaining(HashTable* hashTable, char* key, char* value);

char* getHashName(char valueToChar[], HashTable* hashTable);

char* getHashName(char valueToChar[], HashTable* hashTable)
{
	int test = atoi(valueToChar);
	switch (test)
	{
	case 1:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "1"));
		return SearchHashTable(hashTable, "1");
		break;
	case 2:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "2"));
		return SearchHashTable(hashTable, "2");
		break;
	case 3:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "3"));
		return SearchHashTable(hashTable, "3");
		break;
	case 4:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "4"));
		return SearchHashTable(hashTable, "4");
		break;
	case 5:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "5"));
		return SearchHashTable(hashTable, "5");
		break;
	case 6:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "6"));
		return SearchHashTable(hashTable, "6");
		break;
	case 7:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "7"));
		return SearchHashTable(hashTable, "7");
		break;
	case 8:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "8"));
		return SearchHashTable(hashTable, "8");
		break;
	case 9:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "9"));
		return SearchHashTable(hashTable, "9");
		break;
	case 10:
		//printf("Result for %d: %s\n", test, SearchHashTable(hashTable, "10"));
		return SearchHashTable(hashTable, "10");
		break;

	default:
		break;
	}
}


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

	// Initialize hashTable
	HashTable* hashTable = InitializeHashTable();
	InsertSeparateChaining(hashTable, "1", "a baby");
	InsertSeparateChaining(hashTable, "2", "a child");
	InsertSeparateChaining(hashTable, "3", "teenager");
	InsertSeparateChaining(hashTable, "4", "adult");
	InsertSeparateChaining(hashTable, "5", "dwarf");
	InsertSeparateChaining(hashTable, "6", "elf");
	InsertSeparateChaining(hashTable, "7", "horse");
	InsertSeparateChaining(hashTable, "8", "griffin");
	InsertSeparateChaining(hashTable, "9", "freight train");
	InsertSeparateChaining(hashTable, "10", "dragon");

	getHashName("1", hashTable);


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
		int value = rand() % (4 + 1);
		//InsertNewPlayerAtEnd(i, playerNames[i], &head, &tail);
		InsertNewPlayerSorted(value, playerNames[i], &head, &tail);
	}



	// Generation testing!

	PlayerTurnList* thisCurrent = head;

	do
	{
		printf("Generating rolls for %s: \n", thisCurrent->playerName);
		thisCurrent->generatedRolls = initializePlayerRolls();
		PushTheRolls(thisCurrent->generatedRolls);
		thisCurrent = thisCurrent->NextNode;
	} while (thisCurrent != NULL);

	//head->generatedRolls = initializePlayerRolls();
	//PushTheRolls(head->generatedRolls);
	PrintList(head);
	//printStack(head->generatedRolls);


	int roundNumber = 0;
	while (roundNumber != NUMBER_OF_ROUNDS) // Continue based on number of rounds
	{
		printf("\nDoing turn: %d!\n", roundNumber + 1); // Count the turns

		int winningNumber = 0; // Storage for each rounds winning number
		char winningName[MAX_STRING_SIZE] = { "\0" }; // Storage for each rounds winning name

		PlayerTurnList* currentTurn = head; // To iterate over the players in the turn list
		
		while(currentTurn != NULL) // do/while until the currentTurn is = to the head (circular linked list)
		{
			// Debug printout
			printf("Player %s, value popped: %d\n", currentTurn->playerName, peek(currentTurn->generatedRolls));

			// If the winning number is less than the CURRENT players first roll
			if (winningNumber < peek(currentTurn->generatedRolls))
			{
				// Pop the number off of their stack, and save it and their name
				winningNumber = pop(currentTurn->generatedRolls);
				strcpy(winningName, currentTurn->playerName);
			}

			// Otherwise their number was not the winning number, just pop their value so it's removed
			else
			{
				pop(currentTurn->generatedRolls);
			}

			currentTurn = currentTurn->NextNode; // Step into the next player

		} /*while (currentTurn != NULL)*/;

		

		// Conversion of integer winning number to a string to get the hash value
		char numToStr[3] = { "\0" };
		sprintf(numToStr, "%d", winningNumber);
		//getHashName(numToStr, hashTable);
		printf("%s DESTROYED everyone with a : %s\n", winningName, getHashName(numToStr, hashTable));

		printf("Round Winner: %s, winning value: %d\n", winningName, winningNumber); // Who won the round?
		// Code here for pushing the wins onto the stack

		roundNumber++; // Increment the round number
	}

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


void InsertNewPlayerSorted(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail)
{
	PlayerTurnList* newNode = CreateNewNode(newPlayerRotationNumber, playerName); // Create a new node

	if (*head == NULL || newPlayerRotationNumber < (*head)->playerRotationNumber)
	{
		// If the list is empty or the new node should be inserted before the head
		newNode->NextNode = *head;
		*head = newNode;
		if (*tail == NULL)
		{
			// If the list was empty, update tail
			*tail = newNode;
		}
		else if (newPlayerRotationNumber > (*tail)->playerRotationNumber)
		{
			// If the new node should be inserted after the tail, update tail
			(*tail)->NextNode = newNode;
			*tail = newNode;
		}
		return;
	}

	PlayerTurnList* current = *head;
	while (current->NextNode != NULL && current->NextNode->playerRotationNumber < newPlayerRotationNumber)
	{
		// Traverse the list until finding the correct position
		current = current->NextNode;
	}

	// Insert the new node between current and current->NextNode
	newNode->NextNode = current->NextNode;
	current->NextNode = newNode;

	if (newNode->NextNode == NULL)
	{
		// If the new node is inserted at the end, update tail
		*tail = newNode;
	}
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
	} while (current != NULL);

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

int pop(PlayerRolls* stack)
{
	if (isStackEmpty(stack)) // If the stack is empty, what's the point?
	{
		printf("Stack underflow exception");
		exit(EXIT_FAILURE);
	}

	return stack->rolls[stack->topIndex--]; // Otherwise return the previous item as the new topIndex (by decrementing the topIndex!)
}

int peek(PlayerRolls* stack)
{
	if (isStackEmpty(stack))
	{
		printf("No items to view");
		return;
	}

	return stack->rolls[stack->topIndex]; // Take a look at the top of the stack!
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

	return rand() % 10/* + 1*/; // Generate a random number between 1 and 10

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


int GenerateHash(char* word)
{
	int hash = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		int asciiValue = word[i];
		hash = (hash + (asciiValue)) % HASH_TABLE_SIZE;
	}

	return hash;
}



KeyValuePair* InitializeKeyValuePair(char* key, char* value)
{
	KeyValuePair* newKeyValuePair = (KeyValuePair*)malloc(sizeof(KeyValuePair)); // Allocate memory for a new KeyValuePair

	if (newKeyValuePair == NULL)
	{
		printf("EOM");
		exit(EXIT_FAILURE);
	}

	newKeyValuePair->key = strdup(key); // strdup() makes a pointer string, and copies the data to that memory location (key would contain the "word", but a copy in memory)
	newKeyValuePair->value = strdup(value);
	newKeyValuePair->NextKeyValuePair = NULL;
	return newKeyValuePair;
}

HashTable* InitializeHashTable(void)
{
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable)); // Allocate memory for the HashTable

	if (hashTable == NULL) // If it's null, no memory
	{
		printf("EOM");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++) // Iterate over the hashTable TABLE and initialize all values to NULL
	{
		hashTable->Table[i] = NULL;
	}

	return hashTable;
}



char* SearchHashTable(HashTable* hashTable, char* keyToFind)
{
	int hash = GenerateHash(keyToFind);

	if (hashTable->Table[hash] == NULL)
	{
		return "ERROR: cannot find the Key in the table!";
	}

	KeyValuePair* current = hashTable->Table[hash];

	/*if(current->NextKeyValuePair == NULL && strcmp(current->Word, word) == 0){
		return current->Synonym;
	}*/

	while (current != NULL)
	{
		if (strcmp(current->key, keyToFind) == 0)
		{
			return current->value;
		}
		current = current->NextKeyValuePair;
	}

	return "ERROR: cannot find the Key in the table!";
}

void InsertSeparateChaining(HashTable* hashTable, char* key, char* value)
{
	KeyValuePair* kvp = InitializeKeyValuePair(key, value); // Initialize the key/value pair passed in

	int hash = GenerateHash(key); // Generate an int hash for the key provided (one, two, three etc.)

	if (hashTable->Table[hash] == NULL) // If the table location which uses the hash is empty
	{
		hashTable->Table[hash] = kvp; // Assign the KvP to the specified table index (based on hash int)
		return;
	}

	// If there was a collision
	KeyValuePair* current = hashTable->Table[hash];

	while (current->NextKeyValuePair != NULL)
	{
		current = current->NextKeyValuePair;
	}
	current->NextKeyValuePair = kvp;
}

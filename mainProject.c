#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#pragma warning(disable:4996)

#define MAX_STRING_SIZE 151
#define MAX_NUM_PLAYERS 4
#define MAX_DIE_SIDES 10
#define NUMBER_OF_ROUNDS 5
#define HASH_TABLE_SIZE 20

// Player Turn List (circular array)
typedef struct PlayerTurnList
{
	int playerRotationNumber;
	char playerName[MAX_STRING_SIZE];
	int numberOfRoundsWon;
	struct PlayerRolls* generatedRolls;
	struct PlayerTurnList* NextNode;
} PlayerTurnList;

//typedef struct GameResults // Used for storing the game results
//{
//	int* score;
//	char* playerName[MAX_STRING_SIZE];
//	int topIndex;
//} GameResults;

typedef struct GameResults
{
	int score[MAX_DIE_SIDES]; // Array to store scores for each round
	char playerName[MAX_NUM_PLAYERS][MAX_STRING_SIZE]; // Array to store player names
	int topIndex; // Index to track the top of the stack
} GameResults;

// Player rolls stacks (stack)
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

PlayerTurnList* createNewPlayer(int newPlayerRotationNumber, char playerName[]);
void insertNewPlayerAtEnd(int newPlayerRotationNumber, char playerName[], PlayerTurnList** head, PlayerTurnList** tail);
void printPlayerTurns(PlayerTurnList* head);

PlayerRolls* initializePlayerRolls(void);
void pushPlayerRolls(PlayerRolls* stack);
void push(PlayerRolls* stack, int elementToAdd);
int pop(PlayerRolls* stack);
int peek(PlayerRolls* stack);
void printPlayerRollStacks(PlayerRolls* stack);
bool isStackEmpty(PlayerRolls* stack);
bool isStackFull(PlayerRolls* stack);

GameResults* initializeGameResultsStack(void);
void pushPlayerWin(GameResults* stack, char addPlayerName[]);
int popPlayerWins(GameResults* stack);
int peekPlayerWins(GameResults* stack);
void printPlayerWinsStack(GameResults* resultStack, PlayerTurnList* playerCircular, int playerCount);
bool isResultsStackEmpty(GameResults* stack);
bool isResultsStackFull(GameResults* stack);

HashTable* initializeHashTable(void);
HashTable* setupHashTable();
KeyValuePair* initializeKeyValuePair(char* key, char* value);
int generateHash(char* word);
void insertHashKeyValuePair(HashTable* hashTable, char* key, char* value);
char* searchHashTable(HashTable* hashTable, char* keyToFind);

void waitForInput();
char* convertIntToString(int valueToChange);
int getIntFromUser(void);
void clearCarriageReturn(char buffer[]);
void setupPlayerNames(char nameArray[][MAX_STRING_SIZE], int playerCount);
int randomNumberGenerator();
void insertNewPlayerSorted(int newPlayerRotationNumber, char playerName[], PlayerTurnList** head, PlayerTurnList** tail);

GameResults* initializeGameResultsStack(void)
{
	GameResults* stack = (GameResults*)malloc(sizeof(GameResults));
	if (stack == NULL)
	{
		printf("\nNo memory available! Exiting program.\n");
		exit(EXIT_FAILURE);
	}

	// Initialize scores and player names
	for (int i = 0; i < MAX_DIE_SIDES; i++)
	{
		stack->score[i] = 0;
	}
	for (int i = 0; i < MAX_NUM_PLAYERS; i++)
	{
		strcpy(stack->playerName[i], "");
	}

	stack->topIndex = -1;
	return stack;
}

//GameResults* initializeGameResultsStack(void)
//{
//
//	GameResults* stack = (GameResults*)malloc(sizeof(GameResults));
//	if (stack == NULL)
//	{
//		printf("\nNo memory available! Exiting program.\n");
//		exit(EXIT_FAILURE);
//	}
//
//	stack->score = (int*)malloc(sizeof(int) * MAX_DIE_SIDES);
//
//
//	if (stack->score == NULL)
//	{
//		printf("No memory to initialize stack data member, exiting.");
//		exit(EXIT_FAILURE);
//	}
//
//	for (int i = 0; i < MAX_STRING_SIZE; i++)
//	{
//		stack->playerName[i] = (char*)malloc(sizeof(char) * NUMBER_OF_ROUNDS);
//		if (stack->playerName[i] == NULL)
//		{
//			printf("out of memory error\n");
//			exit(EXIT_FAILURE);
//		}
//	}
//
//	//stack->score = (int*)malloc(sizeof(int) * NUMBER_OF_ROUNDS);
//	//if (stack->score == NULL)
//	//{
//	//	printf("Out of memory!\n");
//	//	exit(EXIT_FAILURE);
//	//}
//
//	//stack->score = 0;
//	stack->topIndex = -1;
//	return stack;
//
//}

void pushPlayerWin(GameResults* stack, char addPlayerName[])
{
	if (isResultsStackFull(stack))
	{
		printf("\nStack Overflow Exception\n");
		exit(EXIT_FAILURE);
	}
	strcpy(stack->playerName[++stack->topIndex], addPlayerName);
	//stack->score[++stack->stackSize] = elementToAdd;
	stack->score[stack->topIndex]++;



	// stack->playerName[++stack->stackSize] = elementToAdd;
}

int popPlayerWins(GameResults* stack)
{
	if (isResultsStackEmpty(stack))
	{
		printf("\nNo results to print!\n");
		exit(EXIT_FAILURE);
	}

	return stack->score[stack->topIndex--];
}

int peekPlayerWins(GameResults* stack)
{
	if (isResultsStackEmpty(stack))
	{
		printf("\nNo results to print.\n");
		return 0;
	}

	return stack->score[stack->topIndex];
}

void printPlayerWinsStack(GameResults* resultStack, PlayerTurnList* playerCircular, int playerCount)
{
	int winner[2] = { 0, 0 };

	if (isResultsStackEmpty(resultStack))
	{
		printf("\nNo results to print.\n");
		return;
	}


	printf("\n---PrintOut:---\n");
	for (int i = 0; i < resultStack->topIndex; i++)
	{
		//printf("Round # %d\n", resultStack->roundNumberWon[i] + 1);
		printf("Name: %s\n", resultStack->playerName[i]);
		printf("Score: %d\n", resultStack->score[i]);
		printf("STACK TEST: %s", playerCircular->playerName);
	}

}

bool isResultsStackEmpty(GameResults* stack)
{
	return stack->topIndex == -1;
}

bool isResultsStackFull(GameResults* stack)
{
	return stack->topIndex == NUMBER_OF_ROUNDS;
}

void testCalculateWinner(GameResults* games)
{

	GameResults* currentGame = games;
	int stackIndex = 0;
	do
	{
		printf("WINNERS:\n");
		printf("Name: %s", games->playerName[stackIndex]);
		stackIndex++;
	} while (stackIndex != games->topIndex);
	//printf("TEST OUT: \n\nWINNER:\nName: %s\nNumber of wins: %d\n\n", winningName, winningNumber);
}


int main(void)
{

	srand(time(NULL)); // seed for random numbers

	// Player turns
	PlayerTurnList* head = NULL;
	PlayerTurnList* tail = NULL;

	// Initialize hashTable
	HashTable* diceRollHashTable = setupHashTable();

	GameResults* gameResultStack = initializeGameResultsStack();

	char playerNames[MAX_NUM_PLAYERS][MAX_STRING_SIZE] =
	{
	"Player One",
	"Player Two",
	"Player Three",
	"Player Four"
	};

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
	}

	printf("Setting up game for %d players!\n", numberOfPlayers);

	// Get player names
	setupPlayerNames(playerNames, numberOfPlayers);

	//Insert the players into the circular list
	for (int i = 0; i < numberOfPlayers; i++)
	{
		int randomPlayerRotationValue = rand() % (4 + 1);
		//InsertNewPlayerAtEnd(i, playerNames[i], &head, &tail);
		insertNewPlayerSorted(randomPlayerRotationValue, playerNames[i], &head, &tail);
	}

	// Generate rolls for players
	PlayerTurnList* thisCurrent = head;
	do
	{
		printf("Generating rolls for %s: \n", thisCurrent->playerName);
		thisCurrent->generatedRolls = initializePlayerRolls();
		pushPlayerRolls(thisCurrent->generatedRolls);
		thisCurrent = thisCurrent->NextNode;
	} while (thisCurrent != NULL);

	printf("Press any key to start the round!\n");
	waitForInput();

	// Actual round being played
	int roundNumber = 0;
	int winningNumber = 0; // Storage for each rounds winning number
	char winningName[MAX_STRING_SIZE] = { "\0" }; // Storage for each rounds winning name
	char loopYN = 'N';
	do
	{
		roundNumber = 0;
		printf("The GAME starts here\n\n");
		while (roundNumber != NUMBER_OF_ROUNDS) // Continue based on number of rounds
		{
			printf("\nDoing turn: %d!\n", roundNumber + 1); // Count the turns
			winningNumber = 0;
			strcpy(winningName, "\0");
			//int winningNumber = 0; // Storage for each rounds winning number
			//char winningName[MAX_STRING_SIZE] = { "\0" }; // Storage for each rounds winning name

			PlayerTurnList* currentTurn = head; // To iterate over the players in the turn list

			while (currentTurn != NULL) // do/while until the currentTurn is = to the head (linked list)
			{
				// Debug printout
				printf("Player %s, value popped: %d\n", currentTurn->playerName, peek(currentTurn->generatedRolls));

				// If the winning number is less than the CURRENT players first roll
				if (winningNumber < peek(currentTurn->generatedRolls))
				{
					// Pop the number off of their stack, and save it and their name
					winningNumber = pop(currentTurn->generatedRolls);
					strcpy(winningName, currentTurn->playerName);
					//currentTurn->numberOfWins++;
				}

				// Otherwise their number was not the winning number, just pop their value so it's removed
				else
				{
					pop(currentTurn->generatedRolls);
				}

				if (currentTurn->NextNode != NULL)
				{
					printf("Press any key to see %s's roll!\n", currentTurn->NextNode->playerName);
					waitForInput();
				}

				currentTurn = currentTurn->NextNode; // Step into the next player
			} /*while (currentTurn != NULL)*/;

			PlayerTurnList* checkingWinner = head;
			while (checkingWinner != NULL)
			{
				if (strcmp(checkingWinner->playerName, winningName) == 0)
				{
					checkingWinner->numberOfRoundsWon++;
				}
				checkingWinner = checkingWinner->NextNode;
			}
			// Conversion of integer winning number to a string to get the hash value
			char numToStr[3] = { "\0" };
			sprintf(numToStr, "%d", winningNumber);
			//getHashName(numToStr, hashTable);
			printf("%s DESTROYED everyone with a : %s\n", winningName, searchHashTable(diceRollHashTable, convertIntToString(winningNumber)));/*getHashName(numToStr, hashTable)*/

			printf("Round Winner: %s, winning value: %d\n", winningName, winningNumber); // Who won the round?

			// Code here for pushing the wins onto the stack ---------------------------------------------------
			//pushPlayerWin(gameResultStack, winningNumber, roundNumber, winningName);



			roundNumber++; // Increment the round number
		}

		PlayerTurnList* currentPlayer = head;

		while (currentPlayer != NULL)
		{
			if (strcmp(currentPlayer->playerName, winningName) == 0)
			{
				pushPlayerWin(gameResultStack, winningName);
			}
			currentPlayer = currentPlayer->NextNode;
		}

		// accept input here to loop
		printf("\n\nDo you want to play again? (Y/N): ");

	} while (getch() != 110); 


	printf("Game Results:\n");

	printf("Stack: %d", peekPlayerWins(gameResultStack));
	//testCalculateWinner(head);
	//printPlayerWinsStack(gameResultStack, head, numberOfPlayers);
	printf("Wtf?...");

	//// Free up the memory
	//PlayerTurnList* freeTurns = head;
	//while (freeTurns != NULL)
	//{
	//	free(freeTurns->generatedRolls);
	//	PlayerTurnList* temp = freeTurns;
	//	freeTurns = freeTurns->NextNode;
	//	free(temp);
	//}
	//free(diceRollHashTable);

	return 0;
}

void pushPlayerRolls(PlayerRolls* stack)
{
	if (isStackFull(stack))
	{
		printf("ERROR: Stack for player rolls is full, this shouldn't happen! EXITING\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUMBER_OF_ROUNDS; i++)
	{
		push(stack, randomNumberGenerator());
	}
}

PlayerTurnList* createNewPlayer(int newPlayerRotationNumber, char playerName[])
{
	PlayerTurnList* newPlayerNode = (PlayerTurnList*)malloc(sizeof(PlayerTurnList));
	if (newPlayerNode == NULL)
	{
		printf("No Memory");
		exit(EXIT_FAILURE);
	}

	newPlayerNode->playerRotationNumber = newPlayerRotationNumber;
	newPlayerNode->numberOfRoundsWon = 0;
	strcpy(newPlayerNode->playerName, playerName);
	newPlayerNode->NextNode = NULL;
	return newPlayerNode;
}

// Player Turn List
void insertNewPlayerAtEnd(int newPlayerRotationNumber, char playerName[], PlayerTurnList** head, PlayerTurnList** tail) // Insert a new head
{
	PlayerTurnList* newNode = createNewPlayer(newPlayerRotationNumber, playerName); // New node!

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

void insertNewPlayerSorted(int newPlayerRotationNumber, char playerName[], PlayerTurnList** head, PlayerTurnList** tail)
{
	PlayerTurnList* newNode = createNewPlayer(newPlayerRotationNumber, playerName); // Create a new node

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
void printPlayerTurns(PlayerTurnList* head)
{
	if (head == NULL) // Its empty if the head is null
	{
		printf("No items in list to print!\n");
		return;
	}

	PlayerTurnList* current = head;

	do
	{
		printf("Current Player: %s, rotation Number: %d\n", current->playerName, current->playerRotationNumber);
		printPlayerRollStacks(current->generatedRolls);
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
	stack->rolls = (int*)malloc(sizeof(int) * NUMBER_OF_ROUNDS); // Initialize the rolls stack with number of rounds

	if (stack->rolls == NULL)
	{
		printf("No memory to initialize stack data member, exiting.");
		exit(EXIT_FAILURE);
	}

	stack->topIndex = -1;
	return stack;
}

void push(PlayerRolls* stack, int elementToAdd)
{
	if (isStackFull(stack))
	{
		printf("Stack Overflow Exception");
		exit(EXIT_FAILURE);
	}

	stack->rolls[++stack->topIndex] = elementToAdd;
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
		printf("ERROR - No rolls in the stack to look at!\n");
		return;
	}

	return stack->rolls[stack->topIndex]; // Take a look at the top of the stack!
}

void printPlayerRollStacks(PlayerRolls* stack)
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
	return stack->topIndex == NUMBER_OF_ROUNDS - 1;
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
	return rand() % MAX_DIE_SIDES + 1; // Generate a random number between 1 and 10
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
		char userInput[MAX_STRING_SIZE] = { "\0" };
		char userName[MAX_STRING_SIZE] = { "\0" };

		printf("Enter player %d name (max %i characters): \n", realPlayerCount++, MAX_STRING_SIZE - 1);

		fgets(userName, MAX_STRING_SIZE, stdin);
		clearCarriageReturn(userName);
		while (userName[0] == '\n' || userName[0] == '\0' || userName[0] == ' ')
		{
			printf("Must be a valid URL (max %i characters): ", MAX_STRING_SIZE - 1);
			fgets(userName, MAX_STRING_SIZE, stdin);
		}

		strcpy(nameArray[i], userName);
	}
}

int generateHash(char* word)
{
	int hash = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		int asciiValue = word[i];
		hash = (hash + (asciiValue)) % HASH_TABLE_SIZE;
	}

	return hash;
}

KeyValuePair* initializeKeyValuePair(char* key, char* value)
{
	KeyValuePair* newKeyValuePair = (KeyValuePair*)malloc(sizeof(KeyValuePair));

	if (newKeyValuePair == NULL)
	{
		printf("EOM");
		exit(EXIT_FAILURE);
	}

	newKeyValuePair->key = strdup(key);
	newKeyValuePair->value = strdup(value);
	newKeyValuePair->NextKeyValuePair = NULL;
	return newKeyValuePair;
}

HashTable* initializeHashTable(void)
{
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));

	if (hashTable == NULL)
	{
		printf("EOM");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		hashTable->Table[i] = NULL;
	}

	return hashTable;
}

char* searchHashTable(HashTable* hashTable, char* keyToFind)
{
	int hash = generateHash(keyToFind);

	if (hashTable->Table[hash] == NULL)
	{
		return "ERROR: cannot find the Key in the table!";
	}

	KeyValuePair* current = hashTable->Table[hash];

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

void insertHashKeyValuePair(HashTable* hashTable, char* key, char* value)
{
	KeyValuePair* kvp = initializeKeyValuePair(key, value);

	int hash = generateHash(key);

	if (hashTable->Table[hash] == NULL)
	{
		hashTable->Table[hash] = kvp;
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

void waitForInput()
{
	//char notUsed = getch();
}

char* convertIntToString(int valueToChange)
{
	char numToStr[3] = { "\0" };
	sprintf(numToStr, "%d", valueToChange);
	return numToStr;
}

HashTable* setupHashTable()
{
	HashTable* tableToInitialize = initializeHashTable();
	insertHashKeyValuePair(tableToInitialize, "0", "whisp of air");
	insertHashKeyValuePair(tableToInitialize, "1", "baby");
	insertHashKeyValuePair(tableToInitialize, "2", "child");
	insertHashKeyValuePair(tableToInitialize, "3", "teenager");
	insertHashKeyValuePair(tableToInitialize, "4", "adult");
	insertHashKeyValuePair(tableToInitialize, "5", "dwarf");
	insertHashKeyValuePair(tableToInitialize, "6", "elf");
	insertHashKeyValuePair(tableToInitialize, "7", "horse");
	insertHashKeyValuePair(tableToInitialize, "8", "griffin");
	insertHashKeyValuePair(tableToInitialize, "9", "freight train");
	insertHashKeyValuePair(tableToInitialize, "10", "dragon");
	return tableToInitialize;
}
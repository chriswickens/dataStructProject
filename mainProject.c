#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#pragma warning(disable:4996)

#define MAX_STRING_SIZE 151
#define MAX_NUM_PLAYERS 4
//#define MAX_ROLLS_GENERATED 20
#define NUMBER_OF_ROUNDS 20
#define HASH_TABLE_SIZE 20

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

PlayerTurnList* createNewPlayer(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE]);
void insertNewPlayerAtEnd(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail);
void printPlayerTurns(PlayerTurnList* head);

PlayerRolls* initializePlayerRolls(void);
void pushPlayerRolls(PlayerRolls* stack);
void push(PlayerRolls* stack, int elementToAdd);
int pop(PlayerRolls* stack);
int peek(PlayerRolls* stack);
void printPlayerRollStacks(PlayerRolls* stack);
bool isStackEmpty(PlayerRolls* stack);
bool isStackFull(PlayerRolls* stack);

HashTable* initializeHashTable(void);
HashTable* setupHashTable();
KeyValuePair* initializeKeyValuePair(char* key, char* value);
int generateHash(char* word);
void insertSeparateChaining(HashTable* hashTable, char* key, char* value);
char* searchHashTable(HashTable* hashTable, char* keyToFind);

void waitForInput();
char* convertIntToString(int valueToChange);
int getIntFromUser(void);
void clearCarriageReturn(char buffer[]);
void setupPlayerNames(char nameArray[][MAX_STRING_SIZE], int playerCount);
int randomNumberGenerator();
void insertNewPlayerSorted(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail);

int main(void)
{

	srand(time(NULL)); // seed for random numbers

	// Player turns
	PlayerTurnList* head = NULL;
	PlayerTurnList* tail = NULL;

	// Initialize hashTable
	HashTable* diceRollHashTable = setupHashTable();

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

			if (currentTurn->NextNode != NULL)
			{
				printf("Press any key to see %s's roll!\n", currentTurn->NextNode->playerName);
				waitForInput();
			}

			currentTurn = currentTurn->NextNode; // Step into the next player
		} /*while (currentTurn != NULL)*/;

		// Conversion of integer winning number to a string to get the hash value
		char numToStr[3] = { "\0" };
		sprintf(numToStr, "%d", winningNumber);
		//getHashName(numToStr, hashTable);
		printf("%s DESTROYED everyone with a : %s\n", winningName, searchHashTable(diceRollHashTable, convertIntToString(winningNumber)));/*getHashName(numToStr, hashTable)*/

		printf("Round Winner: %s, winning value: %d\n", winningName, winningNumber); // Who won the round?

		// Code here for pushing the wins onto the stack ---------------------------------------------------

		roundNumber++; // Increment the round number
	}

	printf("Wtf?...");

	// Free up the memory
	PlayerTurnList* freeTurns = head;
	while (freeTurns != NULL)
	{
		free(freeTurns->generatedRolls);
		PlayerTurnList* temp = freeTurns;
		freeTurns = freeTurns->NextNode;
		free(temp);
	}
	free(diceRollHashTable);

	return 0;
}

void pushPlayerRolls(PlayerRolls* stack)
{
	if (isStackFull(stack))
	{
		printf("!!!!! PUSHTHEROLLS() ERROR, STACK IS FULL\n");
		/*return;*/
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < MAX_DIE_SIZE; i++)
	{
		push(stack, randomNumberGenerator());
	}
}

PlayerTurnList* createNewPlayer(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE])
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
void insertNewPlayerAtEnd(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail) // Insert a new head
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

void insertNewPlayerSorted(int newPlayerRotationNumber, char playerName[MAX_STRING_SIZE], PlayerTurnList** head, PlayerTurnList** tail)
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
		printf("list is empty, can't do anything\n");
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
	stack->rolls = (int*)malloc(sizeof(int) * MAX_DIE_SIZE);

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
		printf("No items to view");
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
	return stack->topIndex == MAX_DIE_SIZE - 1;
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
	return rand() % MAX_DIE_SIZE/* + 1*/; // Generate a random number between 1 and 10
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

HashTable* initializeHashTable(void)
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

void insertSeparateChaining(HashTable* hashTable, char* key, char* value)
{
	KeyValuePair* kvp = initializeKeyValuePair(key, value); // Initialize the key/value pair passed in

	int hash = generateHash(key); // Generate an int hash for the key provided (one, two, three etc.)

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
	insertSeparateChaining(tableToInitialize, "0", "whisp of air");
	insertSeparateChaining(tableToInitialize, "1", "baby");
	insertSeparateChaining(tableToInitialize, "2", "child");
	insertSeparateChaining(tableToInitialize, "3", "teenager");
	insertSeparateChaining(tableToInitialize, "4", "adult");
	insertSeparateChaining(tableToInitialize, "5", "dwarf");
	insertSeparateChaining(tableToInitialize, "6", "elf");
	insertSeparateChaining(tableToInitialize, "7", "horse");
	insertSeparateChaining(tableToInitialize, "8", "griffin");
	insertSeparateChaining(tableToInitialize, "9", "freight train");
	insertSeparateChaining(tableToInitialize, "10", "dragon");
	return tableToInitialize;
}
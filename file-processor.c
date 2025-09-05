#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>

/* Constant definitions */
#define N 3

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

char** split(char letter, char* str, int* p_size);
void createFile(char* filename);
char commonestLetter(char* filename);
void decode(char* text);

/* Declarations of auxiliary functions */

int countWord(char letter, char* str);
void printStringsArray(char** A, int size_matrix);
void freeMatrix(char** A, int size_matrix);

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf_s("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-%d : ", N);
				scanf_s("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}


/* Function definitions */

void Ex1()
{
	int p_size;
	char str[100];
	char c;
	char** result = NULL;

	printf("\nWelcome to Ex1! :)\n");
	printf("Please enter letter\n");
	scanf_s(" %c", &c, 1);
	while (getchar() != '\n');

	printf("Please enter sentence\n");
	fgets(str, sizeof(str), stdin);

	result = split(c, str, &p_size);
	printf("\nThe size of the matrix: %d", p_size);
	printStringsArray(result, p_size);
	freeMatrix(result, p_size);
}

void Ex2()
{
	char filename[] = "input.txt";

	printf("\n\nWelcome to Ex2! :)\n");
	createFile(filename);
	commonestLetter(filename);
}

void Ex3()
{
	char text[] = { "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt" };

	printf("\nWelcome to Ex3! :)\n\n");
	printf("BEFORE changes:\n%s\n", text);

	decode(text);

	printf("\nAFTER changes:\n%s\n", text);
}

//qustion 1 - main function
char** split(char letter, char* str, int* p_size)
{
	int amountOfWord = 0, k = 0;
	char currentChar;

	if (strlen(str) == 0) {  //if the string doesn't have any chars in it return 0 (amount Of Words is also 0)
		*p_size = amountOfWord;
		return 0;
	}

	char** matrix = NULL;
	letter = toupper(letter); //change letter to its cap letter
	amountOfWord = countWord(letter, str); //checks how many words are there in the string

	if (amountOfWord == 0) { //if the string doesn't have any words that starts with the chosen letter return 0 (amount Of Words is also 0)
		printf("there is no words with that start with: %c\n", letter);
		*p_size = 0;
		return matrix;
	}

	matrix = (char**)calloc(amountOfWord + 1, sizeof(char*));  //creats matrix with the amount of words as its size
	assert(matrix);

	for (int i = 0; i <= (int)strlen(str); ) //insert the words that starts with the chosen letter to the matrix
	{
		currentChar = toupper(str[i]);
		
		char* searchSpace = (k + 1 == amountOfWord) ? strchr(&str[i], '\n') : strchr(&str[i], ' ');
		
		if (currentChar == letter && (str[i - 1] == ' ' || i == 0))
		{
			int sizeLetter = searchSpace - &str[i];		//subtracts the ptr of the next space char by the ptr of the chosen letter to find the amount of letters
			char* newStr = (char*)calloc(sizeLetter + 1, sizeof(char)); //creats space in the matrix with the amount of letters as its size
			strncpy(newStr, &str[i], sizeLetter);
			i += sizeLetter + 1;
			matrix[k] = newStr; //insert the chosen word to the matrix
			k++;
			continue;
		}
		i++;
	}

	*p_size = amountOfWord;
	return matrix;
}

//qustion 1 - auxiliary functions
int countWord(char letter, char* str)
{
	int sizeMatrix = 0;
	char currentChar;

	if (strlen(str) == 0)
		return 0;

	letter = toupper(letter); //change letter to its cap letter

	for (int i = 0; i <= (int)strlen(str); )
	{
		currentChar = toupper(str[i]);
		if (currentChar == letter && (str[i - 1] == ' ' || i == 0))
		{
			char* searchSpace = strchr(&str[i], ' ');
			int forward = searchSpace - &str[i];   //subtracts the ptr of the next space char by the ptr of the chosen letter to find the ptr of the next word
			i += forward + 1;
			sizeMatrix++; //counts the amount of wordsthat are needed to be inserted into the matrix
			continue;
		}
		i++;
	}
	return sizeMatrix;
}

void printStringsArray(char** A, int size_matrix)
{
	printf("the size of the Strings Array is: %d\n", size_matrix);
	printf("\nYour Strings Array is:\n");
	for (int i = 0; i < size_matrix; i++)
	{
		printf("%s\n", A[i]); //prints each word in the matrix
	}
}

void freeMatrix(char** A, int size_matrix)
{
	for (int i = 0; i < size_matrix; i++)
	{
		free(A[i]); //frees each ptr to word in the matrix
		A[i] = NULL;
	}
	free(A);
	A = NULL;
}


//qustion 2.1 - main function
void createFile(char* filename)
{
	char content[1000], * v1;
	FILE* f = fopen(filename, "w");
	int c;

	if (f == NULL) { //if the wanted file could not be opened
		printf("your file could not be opened\n");
		return;
	}

	while ((c = getchar()) != '\n' && c != EOF); //We used a loop that reads and removes characters from the buffer
												 //until a newline or EOF character is encountered

	printf("please type your string and then press CTRL+Z\n");

	//while (v1 = (fgets(content, sizeof(content), stdin)) != NULL) //prints the wanted string into the file
	while ((v1 = fgets(content, sizeof(content), stdin)) != NULL)
	{
		fputs(content, f);
	}
	printf("\nThe string has been written to the file %s successfully\n", filename);
	fclose(f);
}

//qustion 2.2 - main function
char commonestLetter(char* filename) //finds the commonest Letter in the string
{
	FILE* f = fopen(filename, "r");
	int c, max = 0;
	int countArray[26] = { 0 }; //creats an arrey of counters in the size of the ABC
	char letter;

	if (!f) { //if the wanted file could not be opened
		printf("your file could not be opened\n");
		return '\0';
	}

	while ((c = fgetc(f)) != EOF) //countes how many times each letter repeats itself
	{
		if (isalpha(c)) 
			countArray[toupper(c) - 'A']++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (max <= countArray[i]) { //finds the commonest Letter in the string by comparing their sum of repetition
			max = countArray[i];
			letter = 'A' + i;
		}
	}
	fclose(f);
	printf("\nthe most common letter is: %c\n", letter);

	return letter; //returns the commonest Letter in the string
}

//qustion 3 - main function
void decode(char* text)
{
	int size = strlen(text), count = 1;

	for (int i = 0; i < size; i++)
	{
		if (text[i] != ' ') {
			text[i] = text[i] - count; //subtracts the Hex number of the letter by its distance from the space char and find the new char
			count++;
		}
		else {
			count = 1; //if the space char is encountered reset the count to 1
		}
	}
}
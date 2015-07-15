/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 2  2015 Assignment #1 - hangman program
* Full Name        : Benjamin Symons
* Student Number   : s3435842
* Course Code      : COSC2138/CPT 220
* Start up code provided by the CTeach Team
****************************************************************************/


/* Header files. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Constants. */
#define NUM_WORDS 50
#define ALPHABET_SIZE 26
#define GOOD_GUESS 0
#define BAD_GUESS 1
#define GAME_OVER 1
#define GAME_CONTINUE 0
#define MAX_GUESS 10
#define MAX_WORD_LEN 10

/* Function prototypes. */
void init(char* word);
void displayWord(char* word, int* guessedLetters);
int guessLetter(char* word, int* guessedLetters);
void displayHangman(unsigned wrongGuesses);
int isGameOver(char* word, int* guessedLetters, unsigned wrongGuesses);
void readRestOfLine();

/* Custom Prototypes */
void sline(int x);
#define PUT_STRAIGHT_LINE(num)\
{\
	unsigned lcount;\
	for(lcount = 0; lcount < (num); lcount++){ \
		putchar('-');\
	}\
}

#define BASE 'a'

#define CLEAR()\
{\
	printf("\n");\
}\

int inWord(char* word, char guessed);


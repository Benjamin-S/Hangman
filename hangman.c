/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 2  2015 Assignment #1 - hangman program
* Full Name        : Benjamin Symons
* Student Number   : s3435842
* Course Code      : COSC2138/CPT 220
* Start up code provided by the CTeach Team
****************************************************************************/


#include "hangman.h"

/****************************************************************************
* Function main() is the entry point for the program.
****************************************************************************/
int main(void)
{
   char word[MAX_WORD_LEN + 1];
   unsigned wrongGuesses = 0;
   int guessedLetters[ALPHABET_SIZE] = {
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
   };
   
   time_t t;
   srand((unsigned) time(&t));

   init(word);
   do
   {
      displayWord(word, guessedLetters);
      if(guessLetter(word, guessedLetters) == BAD_GUESS)
      {
         wrongGuesses +=1;
      }
      displayHangman(wrongGuesses);

   }while(isGameOver(word, guessedLetters, wrongGuesses) == GAME_CONTINUE);

   printf("\n%s%s\n", "The word was: ", word);

   return EXIT_SUCCESS;
}


/****************************************************************************
* Function init() choses a word for the hangman game from the words[] array.
****************************************************************************/
void init(char* word)
{
   const char* words[NUM_WORDS] = {
      "array",      "auto",       "break",      "case",       "cast",
      "character",  "comment",    "compiler",   "constant",   "continue",
      "default",    "double",     "dynamic",    "else",       "enum",
      "expression", "extern",     "file",       "float",      "function",
      "goto",       "heap",       "identifier", "library",    "linker",
      "long",       "macro",      "operand",    "operator",   "pointer",
      "prototype",  "recursion",  "register",   "return",     "short",
      "signed",     "sizeof",     "stack",      "statement",  "static",
      "string",     "struct",     "switch",     "typedef",    "union",
      "unsigned",   "variable",   "void",       "volatile",   "while"
   };

   strcpy(word, words[rand() % NUM_WORDS]);
}


/****************************************************************************
* Function displayWord() prints the word to screen with all letters that 
* have not been correctly guessed blanked out with an underscore. 
* Output example:
* +-+-+-+-+-+-+-+-+-+-+
* |i|d|e|n|_|i|_|i|e|r|
* +-+-+-+-+-+-+-+-+-+-+
****************************************************************************/
void displayWord(char* word, int* guessedLetters)
{
   int wordLength;
   char blanked[strlen(word)];

   wordLength = strlen(word);

   /* Create blank word for display */
   for(int x=0; x < wordLength; x++)
   {
      blanked[x] = '_';
   }

   CLEAR();
   /* Decorative Line */
   sline(wordLength);
   /* *************** */

   for(int x=0; x < wordLength; x++)
   {
      for(int y=0; y < ALPHABET_SIZE; y++)
      {
         if(guessedLetters[y] != 0 && guessedLetters[y] == word[x])
         {
            blanked[x] = word[x];
         }
      }
      printf("%c", blanked[x]);
   }
   CLEAR();
   /* Decorative Line */
   sline(wordLength);
   /* *************** */

}


/****************************************************************************
* Function guessLetter() prompts the user to enter one letter. The function
* maintains an array of guessed letters. The function returns GOOD_GUESS
* or BAD_GUESS depending on whether or not the letter is in the word.
****************************************************************************/
int guessLetter(char* word, int* guessedLetters)
{
   char charGuess;
   int arrIndex;

   printf("\n%s", "Please enter one letter: ");
   charGuess = fgetc(stdin);
   readRestOfLine();

   arrIndex = charGuess - BASE;

   if(guessedLetters[arrIndex] != 0)
   {
      printf("\n%s%c%s\n", "The letter ", charGuess, " has already been guessed.");
      return BAD_GUESS;
   }
   else
   {
      guessedLetters[arrIndex] = charGuess;
      if(inWord(word, charGuess))
      {
         return BAD_GUESS;
      }
      else
      {
         return GOOD_GUESS;
      }
   }
   return EXIT_SUCCESS;
}


/****************************************************************************
* Function displayHangman() displays an ascii art drawing to complement the
* game. The drawing varies depending on the number of wrong guesses.
* When there are no wrong guesses, an empty drawing is displayed:
* **********
* *        *
* *        *
* *        *
* *        *
* *        *
* *        *
* **********
* When there are 10 wrong guesses (and the game is over), the complete
* drawing is displayed:
* **********
* * +--+   *
* * |  |   *
* * |  O   *
* * | -+-  *
* * | / \  *
* * +----- *
* **********
* You need to display an appropriate drawing depending on the number of 
* wrong guesses:
* - 0 wrong: empty drawing.
* - 1 wrong: include floor.
* - 2 wrong: include vertical beam.
* - 3 wrong: include horizontal beam.
* - 4 wrong: include noose.
* - 5 wrong: include head.
* - 6 wrong: include body.
* - 7 wrong: include left arm.
* - 8 wrong: include right arm.
* - 9 wrong: include left leg.
* - 10 wrong: include right leg (complete drawing).
****************************************************************************/
void displayHangman(unsigned wrongGuesses)
{
   switch(wrongGuesses)
   {
      case 0:
      printf("\n**********");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n**********");
      break;

      case 1:
      printf("\n**********");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n*        *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 2:
      printf("\n**********");
      printf("\n*        *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 3:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 4:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |  |   *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 5:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |  |   *");
      printf("\n* |  O   *");
      printf("\n* |      *");
      printf("\n* |      *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 6:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |  |   *");
      printf("\n* |  O   *");
      printf("\n* |  +   *");
      printf("\n* |      *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 7:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |  |   *");
      printf("\n* |  O   *");
      printf("\n* | /+   *");
      printf("\n* |      *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 8:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |  |   *");
      printf("\n* |  O   *");
      printf("\n* | /+\\  *");
      printf("\n* |      *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 9:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |  |   *");
      printf("\n* |  O   *");
      printf("\n* | /+\\  *");
      printf("\n* | /    *");
      printf("\n* +----- *");
      printf("\n**********");
      break;

      case 10:
      printf("\n**********");
      printf("\n* +--+   *");
      printf("\n* |  |   *");
      printf("\n* |  O   *");
      printf("\n* | /+\\  *");
      printf("\n* | / \\  *");
      printf("\n* +----- *");
      printf("\n**********");
      break;
   }
}


/****************************************************************************
* Function isGameOver() is the final step in the program. The game is over
* if either all letters in the word have been guessed, or the player has run
* out of guesses. The player is congratulated if he/she wins. The word is
* displayed to the player if he/she loses. This function returns either 
* GAME_OVER or GAME_CONTINUE.
****************************************************************************/
int isGameOver(char* word, int* guessedLetters, unsigned wrongGuesses)
{
   int wordLength;
   wordLength = strlen(word);
   int lettersRemaining = wordLength;

   if(wrongGuesses >= 10)
   {
      printf("\n%s\n", "GAME OVER!");
      return GAME_OVER;
   }

   for(int x=0; x < wordLength; x++)
   {
      for(int y=0; y < ALPHABET_SIZE; y++)
      {
         if(guessedLetters[y] == word[x])
         {
            lettersRemaining -= 1;
         }
      }
   }

   if(lettersRemaining <= 0)
   {
      printf("\n%s\n", "CONGRATULATIONS!");
      return GAME_OVER;
   }
   else
   {
      return GAME_CONTINUE;
   }
}


/****************************************************************************
* Function readRestOfLine() is used for buffer clearing. Source: 
* https://inside.cs.rmit.edu.au/~sdb/teaching/C-Prog/CourseDocuments/
* FrequentlyAskedQuestions/
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}


/* Custom Functions */
void sline(int x)
{
   PUT_STRAIGHT_LINE(x);
   printf("\n");
}

int inWord(char* word, char guessed)
{
   int i = 0;
   while(word[i] != '\0')
   {
      if(word[i] == guessed)
      {
         return EXIT_SUCCESS;
      }
      i +=1;
   }
   return EXIT_FAILURE;
}


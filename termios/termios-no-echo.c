/* File: termios-no-echo.c
 * Author: Matthew Shrider
 * 
 * This program will test the ECHO flag of the terminal settings.
 * First, a user will input to the terminal with ECHO disabled,
 * and then a user will input to the terminal with ECHO enabled.
 */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

char theirWord[64];
struct termios oldterm, newterm;
int fd;

void disableEcho();
void enableEcho();

int main(){

	printf("\nDisabling echo.\n");
   printf("Enter secret word/phrase:");

   disableEcho();

   //Read up to 63 characters from stdin and terminate with 0;
   fgets(theirWord, 63, stdin);
   theirWord[63] = 0;

   enableEcho();

   printf("\nYou entered: %s\n", theirWord);

   printf("Default behavior restored.\n");
   printf("Enter visible word/phrase: ");

   fgets(theirWord, 63, stdin);
   theirWord[63] = 0;

   printf("\n");
	return 0;
}

/* ********************
 * All this function does is re-enable echo by
 * setting the termios flags back to their 
 * original state, before we changed them.
 * **********************/
void enableEcho(){
   tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
}

/* ********************
 * This function saves the state of termios flags into
 * the oldterm struct, and the newterm struct.  It flips 
 * the ECHO masked bits into newterm. Finally, the stdin
 * device termios gets reset with the newterm struct.
 * *********************/
void disableEcho(){
   //Save terminal settings into oldterm and newterm.
   tcgetattr(STDIN_FILENO, &oldterm);
   newterm = oldterm;
 
   //Flip the Echo bits in newterm.
   newterm.c_lflag &= ~(ECHO);
   
   //Save the new settings into the terminal right now.
   tcsetattr(STDIN_FILENO, TCSANOW, &newterm);  
}

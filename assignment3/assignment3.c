/*****************************************
*                 Assignment3            *
*               by: Sam Dinkelman        *
*   This program will print numbers the  *
*   user enters on the command line and  *
*   print the integers in a seven segment*
*   digital display format.              *
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXINPUT  42 //ensures printing wont be messed up

/*This function prints the tops of the
numbers and will check each case against
the number passed to it by main
*/
void top(char input){
  int num = atoi(&input);
  switch (num) {
    case 0:
    printf("  _ ");
    break;
    case 1:
    printf("   ");
    break;
    case 2:
    printf("  _ ");
    break;
    case 3:
    printf(" _  ");
    break;
    case 4:
    printf("    ");
    break;
    case 5:
    printf("  _ ");
    break;
    case 6:
    printf("  _ ");
    break;
    case 7:
    printf(" _  ");
    break;
    case 8:
    printf("  _ ");
    break;
    case 9:
    printf("  _ ");
    break;
  }

}
/*This function prints the middle of the
numbers and will check each case against
the number passed to it by main
*/
void mid(char input){
  int num = atoi(&input);
  switch (num) {
    case 0:
    printf(" | |");
    break;
    case 1:
    printf(" | ");
    break;
    case 2:
    printf("  _|");
    break;
    case 3:
    printf(" _| ");
    break;
    case 4:
    printf(" |_|");
    break;
    case 5:
    printf(" |_ ");
    break;
    case 6:
    printf(" |_ ");
    break;
    case 7:
    printf("  | ");
    break;
    case 8:
    printf(" |_|");
    break;
    case 9:
    printf(" |_|");
    break;
  }

}
/*This function prints the bottom of the
numbers and will check each case against
the number passed to it by main
*/
void bot(char input){
  int num = atoi(&input);
  switch (num) {
    case 0:
    printf(" |_|");
    break;
    case 1:
    printf(" | ");
    break;
    case 2:
    printf(" |_ ");
    break;
    case 3:
    printf(" _| ");
    break;
    case 4:
    printf("   |");
    break;
    case 5:
    printf("  _|");
    break;
    case 6:
    printf(" |_|");
    break;
    case 7:
    printf("  | ");
    break;
    case 8:
    printf(" |_|");
    break;
    case 9:
    printf("  _|");
    break;
  }
}

int main(int argc, char const *argv[]) {
  //makes sure only 2 arguments are on the command line
  if(argc < 2){
    printf("Usage: ./assignment3 \"integer\"\n");
    return 1;
  }if(argc > 2){
    printf("Usage: ./assignment3 \"integer\"\n");
    return 1;
  }
  int i, length;
  //a character array used to store user input
  char input[MAXINPUT] = "";
  //puts user input into character array for manipulation
  sscanf(argv[1], "%s", input);
  length = strlen(input);
  if(length > MAXINPUT){
    printf("You have entered too many numbers.\n");
    exit(1);
  }
  //This will check that the command line arguments are numbers
  for(i = 0; i < length; i++){
    if(!isdigit(input[i])){
      printf("Input is not a number, please enter a number\n");
      exit(1);
    }
  }

  //This will run through the tops of each number
  for(i = 0; i < length; i++){
    top(input[i]);
  }
  printf("\n");

  //This will run through the middle of each number
  for(i = 0; i < length; i++){
    mid(input[i]);
  }
  printf("\n");

  //This will run through the bottom of each number
  for(i = 0; i < length; i++){
    bot(input[i]);
  }
  printf("\n");

  return 0;
}

/****************************************
*               Assignment2             *
*             By Sam Dinkelman          *
*             Date: 11/15/2018          *
* Purpose: The purpose of this program  *
* is to calculate the hamming distance  *
* between two words, one entered by a   *
* user and one from the wordlist. If    *
* we find the word in the wordlist we   *
* dont suggest a word, if we dont find  *
* the word we suggest one from the list *
****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN  40
#define MAX_WORDS     345000
char wordlist[MAX_WORDS][MAX_WORD_LEN];


/*This function will take in the word we enter
and the words from the wordlist and calculate the
hamming distance between the word entered and the
word in the wordlist and return that distance
*/
int hammer(char *word, char *wordlist){
  int i = 0, distance = 0;
  while (i <= strlen(word)){
    if(word[i] != wordlist[i]){
      distance++;
    }
    i++;
  }
  distance -= 1;
  return distance;
}
/*This function will take the file we opened in main
and it will parse out the words into the wordlist array
*/
void openfile(FILE *filein){
  int i;
  for(i = 0; i < MAX_WORDS; i++){
    fgets(wordlist[i], MAX_WORD_LEN, filein);
  }
}

int main(int argc, char const *argv[]){

  printf("Here is the usage of this program: \n./assignment2 wordlist.txt\n\n");
  //This compares the file entered to the two names of files we were given
  char wl1[12], wl2[14], wl3[9], wl4[10], word[MAX_WORD_LEN];
  strcpy(wl1, "wordlist.txt");
  strcpy(wl2, "wordsEn.txt");
  strcpy(wl3, "latin.txt");
  strcpy(wl4, "german.txt");

  /*Check whether the file containing the wordlist is entered*/
  if((strncmp(argv[1], wl1, strlen(wl1)) == 0) || (strncmp(argv[1], wl2, strlen(wl2)) == 0) || (strncmp(argv[1], wl3, strlen(wl3))==0) || (strncmp(argv[1], wl4, strlen(wl4))==0)){
    /*Gets our file and opens it into input*/
    FILE *filein = fopen(argv[1], "r");
    openfile(filein);
    fclose(filein);
  //if we cannot fine the file name we print this statement and exit
  }else{
    printf("We could not find the file name in command line\n");
    exit(0);
  }

  do{
    int count = 0, min = 40, distance = 0, flag = 1;
    /*This will get the word you type into the console*/
    printf("\nPlease enter a word to check:\n");
    fgets(word, MAX_WORD_LEN, stdin);

    /*This will turn the word you enter into lowercase*/
    for(int i = 0; i < strlen(word); i++){
      word[i] = tolower(word[i]);
    }

    printf("You entered: %s\n", word);
    word[strcspn(word, "\n")] = 0; //this strips off the newline character in the word array

      /*This will begin searching through the wordlist
      while the string lengths are equal, it will check
      if the word entered is the same as a word in the wordlist*/
      for(int j = 0; j < MAX_WORDS; j++){\
        //makes sure the words are of equal length
        if(strlen(word) == strlen(wordlist[j])-2){

          //finds a matching word in wordlist
          if(strncmp(word, wordlist[j], strlen(word))==0){
            printf("Word found in Wordlist. No spelling suggestions.\n");
            flag = 1;
            break;
          }

          /*Goes through the wordlist and compares words
          as long as they aren't the same as the word we enter*/
          else if(strncmp(word, wordlist[j], strlen(word)) != 0){
              distance = hammer(word, wordlist[j]);//stores the value of the hamming distance
              flag = 0;//turn flag to 0
              if(distance < min){//checks that distance is valid
                min = distance;//set the value equal to the distance for later
              }
            }
          }
        }

      /*Runs through the wordlist again */
      for(int k = 0; k < MAX_WORDS; k++){
        //makes sure the words are of equal length
        if(strlen(word) == strlen(wordlist[k])-2){
          distance = hammer(word, wordlist[k]);//stores the value of the hamming distance

          /*Runs if the distance is equal to the minimum which we set earlier
          also only runs 5 times using count and if the flag got set earlier */
          if(min == distance && count < 5 && flag == 0){
            printf("Did you mean?\n%s\n", wordlist[k]);//prints the suggestions
            count++;
          }
        }
      }
  }while(strlen(word) != 0);//stop running the checks and exits if the word is 0 length
  return 0;
}

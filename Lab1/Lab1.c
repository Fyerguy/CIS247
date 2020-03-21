/*
 * Lab1.c
 * CSCI 247, Lab exercise 1, Summer, 2017
 * 
 * David Bover, June, 2017
 * 
 */

#include <stdio.h>
#include <string.h>


#define MAX_LINE    1024

// function find()
// searches for a substring in a string
// parameters:
//      substr: the substring to be found
//      str: the string to be searched for the substring
// return:
//      position in str where the substring starts, or
//      -1, if the substring was not found in str

int find(char *substr, char *str){
	int i, j = 0, flag;
	for(i = 0; i < strlen(str); i++){
		if(str[i] == substr[0]){
			flag = 0; 
			for(j = 1; j < strlen(substr); j++){
				if(str[i+j] != substr[j]){
					flag = 1;
				}
			}
			if(flag == 0){
				return i;	
			}
		}
	}
	return (-1);
}			
// function replace
// replace part of a string by another string
// parameters:
//      str: the string to be modified
//      pos: the index in str where the modified string is to start
//      newstr: the substring to be used to modify str
void replace(char *str, int pos, char *substr){
	for(int i = 0; i < strlen(substr); i++){
		str[i+pos] = substr[i];
	}
}
int main (int argc, char *argv[]) {
    
    // check for 3 command-line arguments
    if (argc < 3) {
        puts("Usage: ./Lab1 word1 word2\n");
        return 1;
    }
    
    // check that word1 and word2 are of equal length
    if (strlen(argv[1]) != strlen(argv[2])) {
        puts("The two words must have the same length\n");
        return 1;
    }
    
    // for each line of input, perform string replacement
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, stdin)) {
        
        // remove the \n from the end of the line
        line[strlen(line)-1] = 0;
        
        // find word1 in line
        int pos = find(argv[1], line);
        
        // while word1 found in line, replace it
        while (pos >= 0) {
            replace(line, pos, argv[2]);
            pos = find(argv[1], line);
        }
        
        puts(line);
    }
}

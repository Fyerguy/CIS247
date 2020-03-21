#include <stdio.h>
#include <string.h>
#include <math.h>

/*This function reduces the amount of bits in the given passkey by the most significant digit
turning it into a septet*/

unsigned int reduce_bits(unsigned int bits){
	
}

/*returns the integer value of a specified subsequence of 32 bits
width is the number of bits to be extracted
index width is the index of the rightmost bit to extract*/

unsigned int get_n_bits(unsigned int bits, int width, int index){
        char line[8];
	width = 7;
        //get the next 7 characters of input (leaving space for the null at the end)
        while(fgets(line,8,stdin)){
                //convert to a number
                sscanf(line, "%x", &bits);
        }
	printf("Here are the bits: %d \n", bits);
	return bits;
}

//extracts two 28-bit keys from 4 bytes

void get_keys(char *twokeys[7], unsigned *key1, unsigned *key2){
		
	
	
}


//given a sequence of 7 bits, rotate 3 bits to the left

unsigned int rotate_left3(unsigned bits){
	
}

//shuffle the 7 nibbles according to the pattern

void shuffle_nibbles(unsigned *bits){
	
}

//decode a block of 28 bits

void decode_28bits(unsigned cipher, char *plain, unsigned key1, unsigned key2){
	
}

int main(int argV, char *passkey[]){
	//checks to make sure the proper parameters are entered
	if (argV < 2){
		printf("Usage: ./decrypt passkey\n");
		return 0;
	}
	
	
	
}

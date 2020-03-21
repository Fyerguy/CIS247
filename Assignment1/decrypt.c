#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*this function gets the full string of two keys
then it splits that into two keys, key1 and key2
then it reduces those keys to 28 bits
*/
void get_keys(char *twokeys, unsigned *key1, unsigned *key2){
	int i, nib = 4, nibs = 24;
	unsigned keya = 0, keyb = 0;
	//splits the twokeys into key1 and key2
	for(i = 0; i < 4; i++){
			keya = twokeys[i];				//keya equals twokeys at 0
			keyb = twokeys[nib];			//keyb equal twokeys at 4
			nib++;										//increment the second key
			*key1 |= (keya << nibs);	//shift left by 24, 16, 8, 0
			*key2 |= (keyb << nibs);	//OR in 1 byte at a time
			nibs = nibs - 8;					//reduce nibs by 1 byte
	}
	//this turns the 32 bit ints into 28 bit ints
	int j, c = 0, mask = 127; // mask is equal to 0111 1111
	unsigned a = 0, b = 0,sept1 = 0, sept2 = 0;
	for(j = 0; j < 28; j += 8){
			a = ((*key1 >> j) & mask);//shift key1 right 0, 8, 16, 24
			b = ((*key2 >> j) & mask);//AND it with the mask to push the 32 bit values into the variables
			sept1 |= (a << c);				//shift those variables left 0, 7, 14, 21
			sept2 |= (b << c);				//OR them with new variable to store them into 28 bit ints
			c += 7;										//shift our OR'd variables over 7 at a time
	}
	*key1 = sept1;								//set key1 and 2 equal to the two 28 bit ints
	*key2 = sept2;
}

/*This function shuffles the nibbles
they are shuffled according to the diagram in the assignment
*/
void shuffle_nibbles(unsigned *bits){
		unsigned mask = 15; 				//this mask is 1111
		unsigned decrypted = 0;			//this is where we will store our shuffled nibbles into
		decrypted |= ((*bits & mask) << 24); 	//N6 moves left 24 bits
		mask = mask << 4;											//shift the mask to the next nibble
		decrypted |= ((*bits & mask) << 16); 	//N5 moves left 16 bits
		mask = mask << 4;
		decrypted |= ((*bits & mask) << 8); 	//N4 moves left 8 bits
		mask = mask << 4;
		decrypted |= ((*bits & mask) >> 12); 	//N0 moves right 12 bits
		mask = mask << 4;
		decrypted |= ((*bits & mask) >> 8); 	//N2 moves right 8 bits
		mask = mask << 4;
		decrypted |= ((*bits & mask) >> 16); 	//N1 moves right 16 bits
		mask = mask << 4;
		decrypted |= ((*bits & mask) >> 12);	//N3 moves right 12 bits
		mask = mask << 4;
		*bits = decrypted;										//set the pointer at bits equal to our shuffled nibbles
}
/*This function makes splits up the septets
it will take each septet and make it into
its own int for easier rotating left
*/
void septsplit(unsigned *bits, unsigned *sept1, unsigned *sept2, unsigned *sept3, unsigned *sept4){
	unsigned mask = 127; 				//this mask is 0111 1111
	*sept1 |= (*bits & mask);		//OR's a septet with the result of ANDing the bits and the mask
	mask = mask << 7;						//shift the mask left by 7 for the next septet
	*sept2 |= (*bits & mask);
	mask = mask << 7;
	*sept3 |= (*bits & mask);
	mask = mask << 7;
	*sept4 |= (*bits & mask);
	*sept2 = *sept2 >> 7;				//Now we shift the septets back to the first 7 bits in their ints
	*sept3 = *sept3 >> 14;
	*sept4 = *sept4 >> 21;
}
/*This function takes the septets and
rotates them 3 bits left
*/
unsigned int rotate_left3(unsigned *bits, unsigned *sept1, unsigned *sept2, unsigned *sept3, unsigned *sept4){
	unsigned val1, val2, val3, val4;
	unsigned mask = 896;				//this mask is 0011 1000 0000
	*sept1 = *sept1 << 3;				//shift all the septets left by 3
	*sept2 = *sept2 << 3;				//now we have 3 0's in the LSB
	*sept3 = *sept3 << 3;
	*sept4 = *sept4 << 3;
	val1 = (*sept1 & mask);			//this makes an int with just the 3 left rotated bits in it
	val1 = val1 >> 7;						//then we shift those 3 bits to the first 3 positions
	val2 = (*sept2 & mask);			//we do this for all 4 septets
	val2 = val2 >> 7;
	val3 = (*sept3 & mask);
	val3 = val3 >> 7;
	val4 = (*sept4 & mask);
	val4 = val4 >> 7;
	*sept1 |= val1;							//Now we OR those 3 bits back into sept1
	*sept1 = *sept1 << 25;			//dump the 3 we shifted left in the first step
	*sept1 = *sept1 >> 25;			//and shift back the septet so we get our 7 rotated bits
	*sept2 |= val2;							//we do this for all 4 septets
	*sept2 = *sept2 << 25;
	*sept2 = *sept2 >> 25;
	*sept3 |= val3;
	*sept3 = *sept3 << 25;
	*sept3 = *sept3 >> 25;
	*sept4 |= val4;
	*sept4 = *sept4 << 25;
	*sept4 = *sept4 >>25;
	return 0;
}

int main(int argc, char *argv[]) {
	/* This makes sure that the correct amount
	of arguments are entered*/
	if(argc < 2){
		printf("Usage ./decrypt Password\n");
		return 0;
	}
	unsigned sept1 = 0, sept2 = 0, sept3 = 0, sept4 = 0; //These are used in septsplit and rotate left
	unsigned key1 = 0, key2 = 0;												 //These are the keys which store 28 bits each
	get_keys(argv[1], &key1, &key2);
	unsigned int bits;
	char line[8];
	//get the next 7 characters of input( leaving space for the null at the end)
	while(fgets(line, 8, stdin)){
			//convert to a number
			sscanf(line, "%x", &bits);
			bits = bits ^ key2;					//First XOR with key2
			shuffle_nibbles(&bits);			//passing bits to shuffle nibbles
			bits = bits ^ key1;					//Second XOR with key1
			septsplit(&bits, &sept1, &sept2, &sept3, &sept4);
			rotate_left3(&bits, &sept1, &sept2, &sept3, &sept4);
			printf("%c%c%c%c", sept4, sept3, sept2, sept1);		//prints the final decrypted plaintext
			sept1 = 0;
	}
	return 0;
}

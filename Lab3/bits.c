#include <stdio.h>
#include <math.h>

int main(int argV, char *argC[]){
	int x, y;
//	scanf("%i, %i", &x, &y);
	printf("Here is function 1: %d \n", func1(5,6));
	printf("Here is function 2: %d \n", func2(4,5));
	printf("Here is function 3: %d \n", func3(0x5));
	printf("Here is function 4: %d \n", func4(0xFFFFFFFD));
	printf("Here is function 6: %x \n", func6(0xDEADBEEF, 0, 2));
	return 0;
}

/*This function takes in values x and y
and gives the AND value using only OR and NOT
*/
int func1(int x, int y){
	int a, b;
	a = ~x | ~y;	//Here I NOT x and y and OR them to flip their bits and get the negative value of the two number ORed together
	b = ~a; 	//So here I flip that value that was negative so that it's positive and the value we want
	return b;

}
/* This function takes in value x and y
and it gives the XOR value using only AND and NOT
*/
int func2(int x, int y){
	int a, b, c;
	a = x & y;	//So first I want to get x AND y and store that in a value
	b = ~x & ~y;	//Next I flip the bits of x and y and AND them together
	c = ~a & ~b;	//Then I take these two values and NOT them both to flip them and AND them together to return the value 1
	return c;
}
/*This function returns 1 if any of the
bits that are odd numbered are set to 1
*/

int func3(int x){
	x ^= x >> 16;		//this is XORIng the last 16 bits with the original value
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	x &= 1;		//then we AND the value x has stored with 1 to which will return 1 since in the end the only odd numbers that can be achieved in binary use 1
	return x;
}

int func4(int x){
	int mask = 170;
	mask = (mask << 8) + mask;
	mask = (mask << 16) + mask;
	return !((x & mask) ^ mask);
}

int func6(int x, int m, int n){
	int mask1 = 0xff << (m << 3);
	int mask2 = 0xff << (n << 3);
	int a = (x & mask1) >> (m << 3);
	int b = (x & mask2) >> (n << 3);
	return (x & ~mask1 & ~mask2) | (a << (m << 3)) | (b << (n << 3));
}

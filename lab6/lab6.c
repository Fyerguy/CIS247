/*******************************
*           Lab6               *
*         By: Sam Dinkelman    *
*         11/17/2018           *
*This program does arithmetic  *
*on floating point values the  *
*user enters.                  *
*******************************/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned float_bits;



int float_class(float_bits f){
  return 0;

}

/*This function will return a negative for a positive
floating point value, and a postive for a negative
floating point value
*/

float_bits float_negate(float_bits f){
  int mask = 128;// this is 1000 0000
  mask = mask << 24;//we shift it left by 24 so that 1 is at the signed bit
  //we XOR f and mask to flip the sign bit or preserve it
  f = f ^ mask;
  return f;
}
/*This function will return the absolute value from
zero of a floating point value
*/
float_bits float_absval(float_bits f){
  int mask = 128;//this is 1000 0000
  mask = mask  << 24;//we shift it left by 24 so 1 is at the signed bit
  f = f | mask;//we OR the 1 into the signed bit to flip it
  f = f ^ mask;//we XOR another 1 into signed bit to preserve it
  return f;
}
/*This function will multiply a floating point value
by two
*/
float_bits float_twice(float_bits f){
  int mask = 255, expon = 0, mask3 = 128;
  //move our all 1's mask to the left side to capture the exponent
  mask = mask << 23;
  //preserve the sign bit
  mask3 = mask3 << 24;
  f = f ^ mask3;
  //save exponent in expon
  expon = f & mask;
  //move it to right side for easier manipulation
  expon = expon >> 23;
  //increment exponent
  expon++;
  //move to back to left side
  expon = expon << 23;
  //flip the mask to all 0's
  mask = ~mask;
  //turn f to all zeros
  f = f & mask;
  //put the new exponent back into f and return it
  return f | expon;
}
/*This function will return half the value of
the floating point value
*/
float_bits float_half(float_bits f){
  int mask = 255, expon = 0,  mask3 = 128;
  //move our all 1's mask to the left side to capture the exponent
  mask = mask << 23;
  //preserver the sign bit
  mask3 = mask3 << 24;
  f = f ^ mask3;
  //save the exponent in expon
  expon = f & mask;
  //move it to the right side for easier manipulation
  expon = expon >> 23;
  //subtract 1 from the exponent to halve it
  expon -= 1;
  //move it back to the left side
  expon = expon << 23;
  //flip the mask to all 0's
  mask = ~mask;
  //turn f to all zeros
  f &= mask;
  //put the new exponent back into f and return it
  return f | expon;
}

int main(int argc, char const *argv[]) {
  if(argc < 2){
    printf("Usage: ./lab6 \"floating point number\"\n");
    return 1;
  }
  if(argc > 2){
    printf("Usage: ./lab6 \"floating point number\"\n");
    return 1;
  }

  float_bits fbits;
  float_bits fbits1;
  float_bits fbits2;
  float_bits fbits3;

  sscanf(argv[1], "%f", (float *)&fbits);

  float *f = (float *)&fbits;
  float *f1 = (float *)&fbits1;
  float *f2 = (float *)&fbits2;
  float *f3 = (float *)&fbits3;

  fbits = float_negate(fbits);
  fbits1 = float_absval(fbits);
  fbits2 = float_twice(fbits);
  fbits3 = float_half(fbits);


  printf("Negate: %f\n", *f);
  printf("Absolute: %f\n", *f1);
  printf("Twice: %f\n", *f2);
  printf("Half: %f\n", *f3);

  return 0;
}

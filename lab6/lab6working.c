#include <stdio.h>
#include <stdlib.h>

typedef unsigned float_bits;

int float_class(float_bits f){
  return 0;

}

float_bits float_negate(float_bits f){
  int mask = 128;// this is 1000 0000
  mask = mask << 24;//we shift it left by 24 so that 1 is at the signed bit
  f = f ^ mask;
  return f;
}

float_bits float_absval(float_bits f){
  int mask = 128;
  mask = mask  << 24;
  f = f | mask;
  f = f ^ mask;
  return f;
}

float_bits float_twice(float_bits f){
  int mask = 1, mask2 = 128;
  mask = mask << 23;
  mask2 = mask2 << 24;
  f = f | mask;
  f = f | mask2;
  f = f ^ mask2;
  f = f ^ mask;
  mask++;
  mask = mask << 23;
  f = f ^ mask;
  f = f | mask;
  mask++;
  mask = mask << 23;
  f = f ^ mask;
  f = f | mask;
  return f;
}

float_bits float_half(float_bits f){
  int mask = 1, mask2 = 128;
  mask = mask << 23;
  mask2 = mask2 << 24;
  f = f | mask;
  f = f | mask2;
  f = f ^ mask2;
  mask++;
  mask = mask << 23;
  f = f ^ mask;
  mask++;
  mask = mask << 23;
  f = f ^ mask;
  mask++;
  mask = mask << 23;
  f = f ^ mask;
  return f;
}

int main(int argc, char const *argv[]) {
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


  //printf("%f\n", *f);
  //printf("%f\n", *f1);
  printf("final: %f\n", *f2);
  //printf("%f\n", *f3);

  return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS      125
#define REGROW    17
#define COLUMNS   5
#define BUFFER    30

/*This function brahches and returns 1 if the branch executes
and returns 0 if the branch doesnt execute
x will be the first register
y will be the second register
*/
int branch(char *x, char *y){
  int i, j;
  i = atoi(x);
  j = atoi(y);
  if(i == j){
    return 1;
  }
  return 0;
}
/*this function subtracts the two registers from each other
result will be the first register
x will be the second register
y will be the third register
*/
int sub(char *result, char *x, char *y){
  int i, j, k;
  i = atoi(result);
  j = atoi(x);
  k = atoi(y);
  i = j - k;
  return i;
}
/*This function adds two registers to each other
result will be the first register
x will be the second register
y will be the third register
*/
int add(char *result, char *x, char *y){
  int i, j, k;
  i = atoi(result);
  j = atoi(x);
  k = atoi(y);
  i = j + k;
  return i;
}
/*This function adds a register with an immediate value
x will be the second register
y will be the constant
*/
int addimmediate(char *x, char *y){
  int i = 0, j, k;
  j = atoi(x);
  k = atoi(y);
  i = j + k;
  return i;
}

int main(int argc, char *argv[]){
  /*Opens the file with the mips instructions
  writes to standard error file if it cannot find the file*/
  FILE *fp1 = fopen("instructions.txt", "r");
  if(fp1 == 0){
      fprintf(stderr, "failed to open instructions\n");
      return 1;
  }

  /*Creates the memory array and initializes it
  delimits on commas and spaces as per the format specifiers in sscanf */
  int i = 0, m = 0, hex = 100;
  char *memarray[ROWS][COLUMNS], line[BUFFER];
  while(i < BUFFER && fgets(line, BUFFER-1, fp1)){
    if(sscanf(line, "%[^,], %[^,], %[^,], %[^,], %s", &memarray[i][0], &memarray[i][1], &memarray[i][2], &memarray[i][3], &memarray[i][4])){
      i++;
      m++;
      printf("Here is m: %d\n", m);
    }
  }

  fclose(fp1);

  /*Creates and initializes the register array*/
  char *regarray[17][2];
  regarray [0][0] = "$zero";
  regarray [1][0] = "$a0";
  regarray [2][0] = "$a1";
  regarray [3][0] = "$v0";
  regarray [4][0] = "$v1";
  regarray [5][0] = "$t0";
  regarray [6][0] = "$t1";
  regarray [7][0] = "$t2";
  regarray [8][0] = "$t3";
  regarray [9][0] = "$s0";
  regarray [10][0] = "$s1";
  regarray [11][0] = "$s2";
  regarray [12][0] = "$s3";
  regarray [13][0] = "$s4";
  regarray [14][0] = "$fp";
  regarray [15][0] = "$sp";
  regarray [16][0] = "$ra";

  /*Setting the second column in the regarray to zero*/
  int x = 0;
  char zero[] = {'0', '\0'};
  for(x = 0; x < 17; x++){
    sscanf(zero, "%s", &regarray[x][1]);
  }

  /*Here are the instructions passed to the program*/
  char inst1[] = {'a','d','d','i','\0'};
  char inst2[] = {'a','d','d','\0'};
  char inst3[] = {'b','e','q','\0'};
  char inst4[] = {'s','u','b','\0'};
  char firstinst[] = {'2','0','0','\0'};//Here is the first instruction to be executed

  int a, b, c, d, e, f,  addi1 = 0, addi2 = 0, addi3 = 0, addiresult = 0, add1 = 0, add2 = 0, add3 = 0, add4 = 0, addresult = 0;
  int beq1, beq2, beq3, beqresult, jump, sub1, sub2, sub3, sub4, subresult;
  for(a = 0; a < ROWS; a++){
    if(strcmp(&memarray[a][0], firstinst)==0){//this will check that we are at the first instruction
      for(b = 0; b < ROWS; b++){ //this is a for loop which also works as a program counter
          //finds instruction 1 which is addi
          if(strcmp(&memarray[b][1], inst1) == 0){//find the instruction addi
            addi1 = b;//save the location where we find a matching instruction
            for(c = 0; c < REGROW; c++){
              if(strcmp(&memarray[addi1][2], regarray[c][0]) == 0){//find the first register, the result
                addi2 = c;//save where we find a matching register
              }
              if(strcmp(&memarray[addi1][3], regarray[c][0]) == 0){//find the second register, first operand
                addi3 = c;//save where we find a matching register
              }
            }
            printf("Instruction being executed: %s, %s, %s, %s\n", &memarray[b][1], regarray[addi2][0], regarray[addi3][0], &memarray[b][4]);
            addiresult = addimmediate(&regarray[addi3][1], &memarray[addi1][4]);//call the function and store the return
            printf("Register %s = %s, %s = %s, %s before instruction\n", regarray[addi2][0], &regarray[addi2][1], regarray[addi3][0], &regarray[addi3][1], &memarray[addi1][4]);
            sprintf(&regarray[addi2][1], "%d", addiresult);//store the results into the register array
            printf("Register %s has the value %d after instruction\n\n", regarray[addi2][0], addiresult);
          }
          //finds instruction 2 which is add
          if(strcmp(&memarray[b][1], inst2) ==0){//find the instruction add
            add1 = b;
            for(e = 0; e < REGROW; e++){
              if(strcmp(&memarray[add1][2], regarray[e][0])==0){//find the first reg, the result
                add2 = e;//save where we find a matching register
              }
              if(strcmp(&memarray[add1][3], regarray[e][0])==0){//find the second reg, first operand
                add3 = e;//save where we find a matching register
              }
              if(strcmp(&memarray[add1][4], regarray[e][0])==0){//find the third reg, second operand
                add4 = e;//save where we find a matching register
              }
            }
            printf("Instruction being executed: %s, %s, %s, %s\n", &memarray[b][1], regarray[add2][0], regarray[add3][0], regarray[add4][0]);
            addresult = add(&regarray[add2][1], &regarray[add3][1], &regarray[add4][1]);//call the function and store the return
            printf("Register %s = %s, %s = %s, %s = %s before instruction\n", regarray[add2][0], &regarray[add2][1], regarray[add3][0], &regarray[add3][1], regarray[add4][0], &regarray[add4][1]);
            sprintf(&regarray[add2][1], "%d", addresult);//store the results into the register array
            printf("Register %s has the value %d after instruction\n\n", regarray[add2][0], addresult);
          }
          //finds instruction 3 which is beq
          if(strcmp(&memarray[b][1], inst3)==0){//find the instruction beq
            beq1 = b;
            for(d = 0; d < REGROW; d++){
              if(strcmp(&memarray[beq1][2], regarray[d][0])==0){//find the first reg
                beq2 = d;//save where we find a matching register
              }
              if(strcmp(&memarray[beq1][3], regarray[d][0])==0){//find the second reg
                beq3 = d;//save where we find a matching register
              }
              if(strcmp(&memarray[beq1][4], &memarray[d][0])==0){//find the address to jump to
                jump = d;//save the location of the jump
              }
            }
            printf("Instruction being executed: %s, %s, %s, %s\n", &memarray[b][1], regarray[beq2][0], regarray[beq3][0], &memarray[beq1][4]);
            printf("Registers being compared %s and %s\n", regarray[beq2][0], regarray[beq3][0]);
            beqresult = branch(&regarray[beq2][1], &regarray[beq3][1]);
            if(beqresult == 1){//if the function returns 1 set the program counter to the location of the jump
                printf("After instruction %d lines were jumped\n\n", (d - jump)-1);
                b = jump;
            }else{
                printf("After instruction no lines were jumped\n\n");
            }

          }
          //find instruction 4 which is sub
          if(strcmp(&memarray[b][1], inst4) ==0){//find the instruction sub
            sub1 = b;
            for(f = 0; f < REGROW; f++){
              if(strcmp(&memarray[sub1][2], regarray[f][0])==0){//find the first reg, the result
                sub2 = f;//save where we find a matching register
              }
              if(strcmp(&memarray[sub1][3], regarray[f][0])==0){//find the second reg, first operand
                sub3 = f;//save where we find a matching register
              }
              if(strcmp(&memarray[sub1][4], regarray[f][0])==0){//find the third reg, second operand
                sub4 = f;//save where we find a matching register
              }
            }
            printf("Instruction being executed: %s, %s, %s, %s\n", &memarray[b][1], regarray[sub2][0], regarray[sub3][0], regarray[sub4][0]);
            printf("Register %s = %s, %s = %s, %s = %s before instruction\n", regarray[sub2][0], &regarray[sub2][1], regarray[sub3][0], &regarray[sub3][1], regarray[sub4][0], &regarray[sub4][1]);
            subresult = sub(&regarray[sub2][1], &regarray[sub3][1], &regarray[sub4][1]);
            sprintf(&regarray[sub2][1], "%d", subresult);//store the results into the register array
            printf("Register %s has the value %d after instruction\n\n", regarray[sub2][0], subresult);
          }
      }
    }
  }
  return 0;
}

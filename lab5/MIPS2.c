#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS      1000
#define COLUMNS   5
#define REGARNUM  17
#define BUFFER    50

/*This function will load data from memory to the register
*/
int loadword(char *x, char *y){
  int i, j, k;
  return 0;
}
/*This function will load data from a register to the memory
x is the register the data is stored in
y is the memory we want to store data into
*/
int storeword(char *x, char *y){
  int i, j, k;
  i = atoi(x);
  j = atoi(y);
  i = j;
  return i;
}
/*This function will load an immediate value into a register
x will be the register where the immediate is stored
y will be the register where the immediate value is stored
*/
int loadimmediate(char *x, char *y){
  int i, j;
  i = atoi(x);
  j = atoi(y);
  i = j;
  return i;
}
/*This function will branch on greater than zero
x will be the first register
y will be the second register
*/
int branchgtzero(char *x){
  int i;
  i = atoi(x);
  if(i > 0){
    return 1;
  }
  return 0;
}

/*This function brahches and returns 1 if the brancheq executes
and returns 0 if the brancheq doesnt execute
x will be the first register
y will be the second register
*/
int brancheq(char *x, char *y){
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
unsigned long sub(char *result, char *x, char *y){
  unsigned long i = 0, j = 0, k = 0;
  i = atol(result);
  j = atol(x);
  k = atol(y);
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
unsigned long addimmediateu(char *x, char *y){
  unsigned long i = 0, j=0, k=0, a = 0, b = 0;
  j = atol(x);
  k = atol(y);
  i = j + k;
  return i;
}

int addimmediate(char *x, char *y){
 int i = 0, j, k;
 j = atoi(x);
 k = atoi(y);
 i = j + k;
 return i;
}

int main(int argc, char *argv[]){
  int i = 0, m = 0, hex = 4000, v = 0, a;
  char *memarray[ROWS][COLUMNS], line[BUFFER];

  for(m = ROWS; m >= 0; m--){
    sprintf(&memarray[m][0], "%x", hex);
    sprintf(&memarray[m][1], "%d ", v);
    sprintf(&memarray[m][2], "%d ", v);
    sprintf(&memarray[m][3], "%d ", v);
    sprintf(&memarray[m][4], "%d ", v);
    hex = hex - 4;
  }

  /*Opens the file with the mips instructions
  writes to standard error file if it cannot find the file*/
  FILE *fp1 = fopen("instructions.txt", "r");
  if(fp1 == 0){
      fprintf(stderr, "failed to open instructions\n");
      return 1;
  }

  /*Creates the memory array and initializes it
  delimits on commas and spaces as per the format specifiers in sscanf */
  char *firstinst[100];
  while(fgets(line, BUFFER, fp1)){
      if(sscanf(line, "%[^,], ", &firstinst)){
        for(a = ROWS; a >= 0; a--){
          if(strcmp(&memarray[a][0], &firstinst)==0){
            for(i = 0; i < 100; i++){
              sscanf(line, "%[^,], %[^,], %[^,], %[^,], %s", &memarray[a][0], &memarray[a][1], &memarray[a][2], &memarray[a][3], &memarray[a][4]);
          }
        }
      }
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

  //Here we will put the stack pointer at the end of the memarray
  int sp = 3996;
  sprintf(&regarray[15][1], "%d" ,sp);

  /*Here are the instructions passed to the program*/
  char inst1[] = {'a','d','d','i','u','\0'};
  char inst2[] = {'a','d','d','\0'};
  char inst3[] = {'b','e','q','\0'};
  char inst4[] = {'s','u','b','u','\0'};
  char inst5[] = {'l', 'i', '\0'};
  char inst6[] = {'s','w','\0'};
  char inst7[] = {'a','d','d','i','\0'};
  char inst8[] = {'b','g','t','z','\0'};
  char inst9[] = {'j','\0'};
  char inst10[] = {'j','a','l','\0'};
  char inst11[] = {'j','r','\0'};
  char inst12[] = {'l','w','\0'};

  //this is a large amount of variables for storing locations of instructions and registers
  int bgtz1, bgtz2, bgtzresult, j1, j2, jumpresult, jal1, jal2, jr1, jr2, flag = 1, flag2 = 1;
  int sw1, sw2, sw3, swresult, addi1, addi2, addi3, addiresult, lw1, lw2, lw3, lwresult;
  int addiu1 = 0, addiu2 = 0, addiu3 = 0, sub1, sub2, sub3, sub4, li1, li2, liresult;
  int pc, d, c, e, f, g, h, j, k, l, n, p, q, r, s, t, add1 = 0, add2 = 0, add3 = 0, add4 = 0, addresult = 0;
  int beq1, beq2, beq3, beqresult, jump, jump2;


  for(pc = 0; pc < ROWS; pc++){ //this is a for loop which also works as my program counter

      //finds instruction 1 which is addiu
      if(strcmp(&memarray[pc][1], inst1) == 0){//find the instruction addi
        addiu1 = pc;//save the location where we find a matching instruction
        for(c = 0; c < REGARNUM; c++){
          if(strcmp(&memarray[addiu1][2], regarray[c][0]) == 0){//find the first register, the result
            addiu2 = c;//save where we find a matching register
          }
          if(strcmp(&memarray[addiu1][3], regarray[c][0]) == 0){//find the second register, first operand
            addiu3 = c;//save where we find a matching register
          }
        }
        printf("Instruction being executed: %s, %s, %s, %s \nprogram counter: %s\n stack pointer: %x\n", &memarray[pc][1], regarray[addiu2][0], regarray[addiu3][0], &memarray[pc][4], &memarray[pc+1][0], sp);
        unsigned long addiuresult = addimmediateu(&regarray[addiu3][1], &memarray[addiu1][4]);//call the function and store the return
        printf("Register %s had %s before instruction\n", regarray[addiu2][0], &regarray[addiu2][1]);
        sprintf(&regarray[addiu2][1], "%lu", addiuresult);//store the results into the register array
        printf("Register %s has the value %d after instruction\n\n", regarray[addiu2][0], addiuresult);
      }

      //finds instruction 2 which is add
      if(strcmp(&memarray[pc][1], inst2) ==0){//find the instruction add
        add1 = pc;
        for(e = 0; e < REGARNUM; e++){
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
        printf("Instruction being executed: %s, %s, %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[pc][1], regarray[add2][0], regarray[add3][0], regarray[add4][0], &memarray[pc+1][0], sp);
        addresult = add(&regarray[add2][1], &regarray[add3][1], &regarray[add4][1]);//call the function and store the return
        printf("Register %s had %s before instruction\n", regarray[add2][0], &regarray[add2][1]);
        sprintf(&regarray[add2][1], "%d", addresult);//store the results into the register array
        printf("Register %s has the value %d after instruction\n\n", regarray[add2][0], addresult);
      }

      //finds instruction 3 which is beq
      if(strcmp(&memarray[pc][1], inst3)==0){//find the instruction beq
        beq1 = pc;
        for(d = 0; d < REGARNUM; d++){
          if(strcmp(&memarray[beq1][2], regarray[d][0])==0){//find the first reg
            beq2 = d;//save where we find a matching register
          }
          if(strcmp(&memarray[beq1][3], regarray[d][0])==0){//find the second reg
            beq3 = d;//save where we find a matching register
          }
        for(int r = 0; r < ROWS; r++){
            if(strcmp(&memarray[beq1][4], &memarray[r][0])==0){//find the address to jump to
              jump = r;//save the location of the jump
            }
          }
        }
        printf("Instruction being executed: %s, %s, %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[pc][1], regarray[beq2][0], regarray[beq3][0], &memarray[beq1][4], &memarray[pc+1][0], sp);
        printf("Registers being compared %s and %s\n", regarray[beq2][0], regarray[beq3][0]);
        beqresult = brancheq(&regarray[beq2][1], &regarray[beq3][1]);
        if(beqresult == 1){//if the function returns 1 set the program counter to the location of the jump
            printf("After instruction we branched to address %s\n\n", &memarray[beq1][4]);
            pc = jump;
        }else{
            printf("After instruction no lines were jumped\n\n");
        }
      }

      //find instruction 4 which is subu
      if(strcmp(&memarray[pc][1], inst4) ==0){//find the instruction sub
        sub1 = pc;
        for(f = 0; f < REGARNUM; f++){
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
        printf("Instruction being executed: %s, %s, %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[pc][1], regarray[sub2][0], regarray[sub3][0], regarray[sub4][0], &memarray[pc+1][0], sp);
        printf("Register %s had %s before instruction\n", regarray[sub2][0], &regarray[sub2][1]);
        unsigned long subresult = sub(&regarray[sub2][1], &regarray[sub3][1], &regarray[sub4][1]);
        sprintf(&regarray[sub2][1], "%lu", subresult);//store the results into the register array
        printf("Register %s has the value %d after instruction\n\n", regarray[sub2][0], subresult);
      }

      //find instruction 5 which is li
      if(strcmp(&memarray[pc][1], inst5)==0){//find the li instructions
        li1 = pc;//save that location
        for(g = 0; g < REGARNUM; g++){//lookup for registers
          if(strcmp(&memarray[li1][2], regarray[g][0])==0){//find the first register
            li2 = g;//save that location
          }
        }
      printf("Instruction being executed: %s, %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[pc][1], regarray[li2][0], &memarray[pc][3], &memarray[pc+1][0], sp);
      printf("Register %s had %s before instruction\n", regarray[li2][0], &regarray[li2][1]);
      liresult = loadimmediate(&regarray[li1][1], &memarray[li1][3]);//pass the immediate value and the register value to li function
      sprintf(&regarray[li2][1], "%d", liresult);//feed the result back into the register
      printf("Register %s has the value %d after instruction\n\n",regarray[li2][0], liresult);
    }


    //finds instruction 6 which is sw
    if(strcmp(&memarray[pc][1], inst6)==0){
      sw1 = pc;
      for(h = 0; h < REGARNUM; h++){
        if(strcmp(&memarray[sw1][2], regarray[h][0])==0){//find the first Register
          sw2 = h;
        }
        if(strcmp(&memarray[sw1][3], regarray[h][0])==0){//find the second Register
          sw3 = h;
        }
      }
      printf("Instruction being executed: %s, %s, %s \nprogram counter: %s\n Here is the stack pointer: %x\n", &memarray[pc][1], regarray[sw2][0], regarray[sw3][0], &memarray[pc+1][0], sp);
      printf("Register %s had %s before instruction\n", regarray[sw2][0], &regarray[sw2][1]);
      swresult = storeword(&regarray[sw2][1], &regarray[sw3][1]);
      sprintf(&regarray[sw2][1], "%d", swresult);
      printf("Register %s has the value %d after instruction\n\n",regarray[sw2][0], swresult);
      }

      //finds instruction 1 which is addi
      if(strcmp(&memarray[pc][1], inst7) == 0){//find the instruction addi
        addi1 = pc;//save the location where we find a matching instruction
        for(j = 0; j < REGARNUM; j++){
          if(strcmp(&memarray[addi1][2], regarray[j][0]) == 0){//find the first register, the result
            addi2 = j;//save where we find a matching register
          }
          if(strcmp(&memarray[addi1][3], regarray[j][0]) == 0){//find the second register, first operand
            addi3 = j;//save where we find a matching register
          }
        }
        printf("Instruction being executed: %s, %s, %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[pc][1], regarray[addi2][0], regarray[addi3][0], &memarray[pc][4], &memarray[pc+1][0], sp);
        addiresult = addimmediate(&regarray[addi3][1], &memarray[addi1][4]);//call the function and store the return
        printf("Register %s had %s before instruction\n", regarray[addi2][0], &regarray[addi2][1]);
        sprintf(&regarray[addi2][1], "%d", addiresult);//store the results into the register array
        printf("Register %s has the value %d after instruction\n\n", regarray[addi2][0], addiresult);
      }

      //Looks for instruction 8 which is branch greater than zero
      if(strcmp(&memarray[pc][1], inst8)==0){//find instruction bgtz
        bgtz1 = pc;//save the loation where we find a matching Instruction
        for(k = 0; k < REGARNUM; k++){//lookup for registers
          if(strcmp(&memarray[bgtz1][2], regarray[k][0])==0){//find the first register
            bgtz2 = k;//save the location of the first register
          }
          for(l = 0; l < ROWS; l++){//lookup for memory address to branch to
            if(strcmp(&memarray[bgtz1][3], &memarray[l][0])==0){//find the location to branch to
              jump2 = l;//save the location to branch to
            }
          }
        }
        printf("Instruction being executed: %s, %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[pc][1], regarray[bgtz2][0], &memarray[bgtz1][3], &memarray[pc+1][0], sp);
        printf("Comparing %s to 0\n",regarray[bgtz2][0]);
        bgtzresult = branchgtzero(&regarray[bgtz2][1]);//pass register value to see if its greater than zero
        if(bgtzresult == 1){//get 1 back if it is greater than zero
          printf("After instruction we branched to address %s\n\n", &memarray[bgtz1][3]);
          pc = jump2 ;//branch to the correct memory address if true
        }else{
          printf("After instruction no lines were jumped\n\n");
        }
      }

      //looks for instruction 9 which is jump
      if(strcmp(&memarray[pc][1], inst9)==0){//find j Instruction
        j1 = pc;//save the location of the jump instruction
        for(p = 0; p < ROWS; p++){//lookup for the memory location to jump to
          if(strcmp(&memarray[j1][2], &memarray[p][0])==0){//find the memory location to jump to
            j2 = p;//save that memory location
          }
        }
        printf("Instruction being executed: %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[j1][1], &memarray[j1][2], &memarray[pc+1][0], sp);
        printf("We will now jump %d lines\n\n", pc - j2 -1);
        int holdjump = pc - j2;//find the difference between where we are at and where the jump is
        pc = pc - holdjump -1;//jump to that location
      }

      //Looks for instruction 10 which is jal
      if(strcmp(&memarray[pc][1], inst10)==0 && flag == 1){//find the jal instruction
        jal1 = pc;//save the location of that instruction
        for(r = 0; r < ROWS; r++){//lookup for memory address of jump
          if(strcmp(&memarray[jal1][2], &memarray[r][0])==0){//find the memory address to jump to
            jal2 = r;//save that location
          }
        }
        printf("Instruction being executed: %s, %s \nprogram counter: %s\nstack pointer: %x\n", &memarray[jal1][1], &memarray[jal1][2], &memarray[pc+1][0], sp);
        printf("We will now store %s in the register $ra\n\n", &memarray[jal1+1][0]);
        sprintf(&regarray[16][1], "%s", &memarray[jal1][0]);//feed next instruction location into $ra register
        if(flag == 1){
          pc = jal2;
          flag = 0;
        }
      }

      //Looks for instruction 11 which is jump register
      if (strcmp(&memarray[pc][1], inst11)==0 && flag2 == 1){//find the jr Instruction
        jr1 = pc;//save that location
        for(s = 0; s < ROWS; s++){
          if(strcmp(&memarray[s][0], &regarray[16][1])==0){
            jr2 = s;
          }
        }
        printf("Instruction being executed: %s, %s\nprogram counter: %s\n stack pointer: %x\n", &memarray[jr1][1], &memarray[jr1][2], &memarray[pc+1][0], sp);
        printf("We will now jump to %s which holds the address %s\n\n", &memarray[jr1][2], &memarray[jal1+1][0]);
        if(flag2 == 1){
          pc = jr2;
          flag2 = 0;
        }else if(strcmp(&regarray[16][1], '0')==0){
          exit(0);
        }
      }

      //looks for instruction 12 which is lw
      if(strcmp(&memarray[pc][1], inst12)==0){
        lw1 = pc;
        for(t = 0; t < REGARNUM; t++){
          if(strcmp(&memarray[lw1][2], &regarray[t][0])==0){
            lw2 = t;
          }
          if(strcmp(&memarray[lw1][3], &regarray[t][0])==0){
            lw3 = t;
          }
        }
        printf("Instruction being executed: %s, %s, %s\nprogram counter: %s\nstack pointer: %x\n", &memarray[lw1][1], &memarray[lw1][2], &memarray[lw1][3], &memarray[pc+1][0], sp);
        printf("After instruction the value of %s was stored at %s\n\n", &memarray[lw1][3], &memarray[lw1][2]);
        sp = atoi(&regarray[lw3][1]);
        strcpy(&regarray[lw2][1], &memarray[sp][1]);
        printf("Here is memarray: %s\n", &memarray[sp][1]);

      }
  }

  return 0;
}

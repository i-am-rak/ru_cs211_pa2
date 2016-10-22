/*
 * Anuraag Shankar
 * Calc.c Program
 * CS211
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int checkOperation(char * input){//Check the operation
    if(input[0] == '+'){
        return 1;
    }
    else if(input[0] == '-'){
        return 2;
    }
    else if(input[0] == '*'){
        return 3;
    }
    else{
        return 666;//invalid operation
    }
}

int checkSign(char * input){//Check the sign
    if(input[0] == '-'){
        return 1;
    } 
    else{
        return 0; //positive
    }
}

int checkCorrectBase(char x,int base){
    if(((x - '0') < 10) && ((x -'0') < base)){
        return 0;
    }
    else if((base > 10) && (((x - 'A' + 10) < base) || ((x - 'a' + 10) < base))){
        return 0;
    }
    else
        return 1;
}

int checkBase(char * input){ //Check the base
    if(input[0] == '-'){
        if(input[1] == 'b'){
            return 2;
        }
        else if(input[1] == 'd'){
            return 10;
        }
        else if(input[1] == 'o'){
            return 8;
        }
        else if(input [1] == 'x'){
            return 16;
        }
    }
    else if(input[0] == 'b'){
        return 2;
    }
    else if(input[0] == 'd'){
        return 10;
    }
    else if(input[0] == 'o'){
        return 8;
    }
    else if(input [0] == 'x'){
        return 16;
    }
    else{
        return 666;
    }

    return 666;
}
/* //code is no longer used
char * intToBinaryASCII(unsigned int x, char * output){//convert int to ascii
    unsigned int i, n = 0;
    char * cstr = malloc(3);
    output[0] = '\0';
    for(i = 0; i<32; i++){
        n = x>>31;
        cstr[0] = '0' + n;
        cstr[1] = '\0';
        strcat(output,cstr);
        x = x<< 1;
    }

    i = 0;
    while(output[i] == '0'){
        i++;
    }

    cstr = 0;
    free(cstr);
   // printf("test1");
    return output + i;
}

unsigned int binASCIIToInt(char * str){
    int i, value = 0;
    for(i = 0; str[i] != '\0'; i++){
   //   printf("run : %d\n", i);
        switch(str[i])
        {
            case '0':
                value = (value<<1);
                //printf("%d\n", value);
                break;
            case '1':
                value = (value<<1)+1;
                //printf("%d\n", value);
                break;
            default:
                printf("Error: Something went wrong binToASCII");
                return 0;
        }
    }
    //printf("test0");
    return value;
}
*/
char * intToASCII(int x, char * output,int base,int sign){//converts int to ascii
    //char * octChar = "01234567";
    if(sign == 1){
        x = x*-1;
    }
    int i,n = 0;
    char * cstr = malloc(32);
    //char c = 0;
    char * output2 = malloc(32);
    output2[0] = '\0';
    while(x!=0){
        cstr[0]= (x%base) + '0';
        if(x%base > 9){
            n = base - x%base;
            cstr[0] = 'G' - n; 
        }
        cstr[1] = '\0';
        //printf("-%s-\n", cstr);
        strcat(output2,cstr);
        x /= base;    
    }

    i = 0;
    while(i < strlen(output2)){
        output[i] = output2[strlen(output2)-i-1];
        //printf("-%c-\n", output[i]);
        i++;
    }

    cstr = 0;
    free(cstr);
    
    return output;
}

int ASCIIToInt(char * str,int base, int sign) {//converts ascii to int

    int output = 0;
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] >= 'a' && str[i] <= 'f'){
            output = output*base + str[i] - 'a' + 10;
        }
        else if(str[i] >= 'A' && str[i] <= 'F'){
            output = output*base + str[i] - 'A' + 10;
        }
        else
            output = output*base + str[i] - '0';

        i++;
    }

    if(sign == 1){
        output = output *-1;
    }

    return output;
}
/*//No longer used code
unsigned int octASCIIToInt(char * str){
    int i, value = 0;
    for(i = 0; str[i]!= '\0'; i++){
//        printf("run %d\n", i);
        switch(str[i]){
            case '0': value = (value<<3); break;
            case '4': value = (value<<1) + 1;
                      value = (value<<2);
                      break;
            case '2': value = (value<<2) + 1;
                      value = (value<<1);
                      break;
            case '6': value = (value<<1) + 1;
                      value = (value<<1) + 1;
                      value = (value<<1);
                      break;
            case '1': value = (value<<3) + 1;
                      break;
            case '5': value = (value<<1)+1;
                      value = (value<<2)+1;
                      break;
            case '3': value = (value<<2)+1;
                      value = (value<<1)+1;
                      break;
            case '7': value = (value<<1) +1;
                      value = (value<<1) +1;
                      value = (value<<1) +1;
                      break;
            default: printf("not happy %c \n",  str[i]); return 1;
        }
    }
  //  printf("value %d\n", value);
    return value;
}
*/

int main(int argc, char **argv){

    if(argc != 5){
        fprintf(stderr,"ERROR: Incorrect number of inputs\n");
        return 0;
    }

    int operation = 0;
    int sign1 = 0;
    int base1 = 0;
    int sign2 = 0;
    int base2 = 0;
    int value1 = 0;
    int value2 = 0;
    int output = 0;
    int outputSign = 0;
    char baseChar = argv[4][0];
    int base = checkBase(argv[4]);
   
    if(base == 666){
        fprintf(stderr, "ERROR: Incorrect output type\n");
        return 0;
    }

    operation = checkOperation(argv[1]);    
    if(operation == 666){
        fprintf(stderr,"ERROR: Invalid operation '%s'\n", argv[1]);
        return 0;
    }
    //printf("%d , %s\n", operation, argv[1]);
    sign1 = checkSign(argv[2]);
    base1 = checkBase(argv[2]);
    if(base1 == 666){
        fprintf(stderr,"ERROR: Invalid base '%s'\n", argv[2]);
        return 0;
    }

    int i;
    for(i = 1; i < strlen(argv[2]); i++){
        if(checkCorrectBase(argv[2][i],base1)){
            fprintf(stderr, "ERROR: Invalid input\n");
            return 0;
        }
    }

    //printf("%d , %s\n", sign1, argv[2]);
    //printf("%d , %s\n", base1, argv[2]);
    
    sign2 = checkSign(argv[3]);
    base2 = checkBase(argv[3]);
    if(base2 == 666){
        fprintf(stderr,"ERROR: Invalid base '%s'\n", argv[3]);
        return 0;
    }
    for(i = 1; i < strlen(argv[3]); i++){
           if(checkCorrectBase(argv[3][i],base2)){
               fprintf(stderr, "ERROR: Invalid input\n");
               return 0;
           }
       }


    
    switch(base1){
        case(2):
            value1 = ASCIIToInt(argv[2] + 1 + sign1,base1,sign1);
            //char * output = malloc(strlen(argv[2]));
            //printf("b%s\n", intToASCII(value1,output,base1,sign1));
            break; 
        case(8):
            //to be filled
            value1 = ASCIIToInt(argv[2] + 1 + sign1,base1,sign1);
            //char * output2 = malloc(strlen(argv[2]));
            //printf("o%s\n", intToASCII(value1,output2,base1,sign1)); 
            break;
        case(10):
            //to be filled
            value1 = ASCIIToInt(argv[2] + 1 + sign1,base1,sign1);
            //char * output3 = malloc(strlen(argv[2]));
            //printf("o%s\n", intToASCII(value1,output3,base1,sign1)); 
            break;
        case(16):
            //to be filled
            value1 = ASCIIToInt(argv[2] + 1 + sign1,base1,sign1);
            //char * output4 = malloc(strlen(argv[2]));
            //printf("o%s\n", intToASCII(value1,output4,base1,sign1));   
            break;
    }

     switch(base2){
        case(2):
            value2 = ASCIIToInt(argv[3] + 1 + sign2,base2,sign2);
            //char * output = malloc(strlen(argv[2]));
            //printf("b%s\n", intToASCII(value2,output,base2,sign2));
            break; 
        case(8):
            //to be filled
            value2 = ASCIIToInt(argv[3] + 1 + sign2,base2,sign2);
            //char * output2 = malloc(strlen(argv[2]));
            //printf("o%s\n", intToASCII(value1,output2,base1,sign1)); 
            break;
        case(10):
            //to be filled
            value2 = ASCIIToInt(argv[3] + 1 + sign2,base2,sign2);
            //char * output3 = malloc(strlen(argv[2]));
            //printf("o%s\n", intToASCII(value1,output3,base1,sign1)); 
            break;
        case(16):
            //to be filled
            value2 = ASCIIToInt(argv[3] + 1 + sign2,base2,sign2);
            //char * output4 = malloc(strlen(argv[2]));
            //printf("o%s\n", intToASCII(value1,output4,base1,sign1));   
            break;
    }

    switch(operation){
        case 1:
            output = value1 + value2;
            if(output < 0){
                outputSign = 1;
            }
            break;
        case 2:
            output = value1 - value2;
            if(output < 0){
                outputSign = 1;
            }
            break;
         case 3:
            output = value1 * value2;
            if(output < 0) {
                outputSign = 1;
            }
            break;
    }


    char * outputStr = malloc(35);
    char signChar = 0;
    if(outputSign == 1){
        signChar = '-';         
    }

    //you can also use strings and concat
    fprintf(stdout,"%c%c%s\n", signChar,baseChar,intToASCII(output,outputStr,base,outputSign)); 

    //printf("%d , %s\n", sign2, argv[3]); 
    //printf("%d , %s\n", base2, argv[3]);
    
    return 0;
}


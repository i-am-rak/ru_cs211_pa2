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
        return 666;
    }
}

int checkSign(char * input){//Check the sign
    if(input[0] == '-'){
        return 1;
    } 
    else{
        return 0;
    }
}

int checkBase(char * input){ //Check the base
    if(input[0] == '-'){
        if(input[1] == 'b'){
            return 1;
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

char * intToBinaryASCII(unsigned int x, char * output){
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

int main(int argc, char **argv){
    int operation = 0;
    int sign1 = 0;
    int base1 = 0;
    int sign2 = 0;
    int base2 = 0;
    unsigned int value1 = 0;
    unsigned int value2 = 0;

    operation = checkOperation(argv[1]);    
    if(operation == 666){
        printf("Error: Invalid operation '%s'", argv[1]);
        return 0;
    }
    //printf("%d , %s\n", operation, argv[1]);
    sign1 = checkSign(argv[2]);
    base1 = checkBase(argv[2]);
    if(base1 == 666){
        printf("Error: Invalid input '%s'", argv[2]);
        return 0;
    }

    //printf("%d , %s\n", sign1, argv[2]);
    //printf("%d , %s\n", base1, argv[2]);
    
    sign2 = checkSign(argv[3]);
    base2 = checkBase(argv[3]);
    if(base2 == 666){
        printf("Error: Invalid input '%s'", argv[3]);
        return 0;
    }
    
    switch(base1){
        case(2):
            value1 = binASCIIToInt(argv[2] + 1 + sign1);
            char * output = malloc(strlen(argv[2]));
            printf("b%s\n", intToBinaryASCII(value1,output)); 
        case(8):
            //to be filled
            break;
        case(10):
            //to be filled
            break;
        case(16):
            //to be filled
            break;
    }

    //printf("%d , %s\n", sign2, argv[3]); 
    //printf("%d , %s\n", base2, argv[3]);
    
    return 0;
}


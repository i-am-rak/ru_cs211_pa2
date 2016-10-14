#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int checkOperation(char * input){
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


int main(int argc, char **argv){
    int operation = 0;
    operation = checkOperation(argv[1]);
    if(operation == 666){
        printf("Error: Invalid operation '%s'", argv[1]);
    }
    //printf("%d , %s\n", operation, argv[1]);
    
    return 0;
}


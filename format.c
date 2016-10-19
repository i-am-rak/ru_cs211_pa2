#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


char * intToASCII(int x, char * output,int base,int sign){
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

int ASCIIToInt(char * str,int base, int sign) {

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




int main(int argc, char ** argv){
    
    if(argv[2][0] == 'f'){
        char * str = argv[1];
        int *x;
        memcpy(x,str,sizeof(int));
        printf("%d\n",*x);

    }
    else if(argv[2][0] == 'i'){
        char * output = malloc(32);
        int sign = 0;
        char signchar = 0;
        int x = ASCIIToInt(argv[1],2,0);
        if(x < 0){
            sign = 1;
            signchar = '-';
        }
        output = intToASCII(ASCIIToInt(argv[1],2,0),output,10,sign);
        printf("%c%s\n",signchar, output);
        printf("%d\n", x);
    }


    return 0; 
}

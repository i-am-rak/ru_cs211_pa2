/*
 * Anuraag Shankar
 * Format.c Program
 * CS211
 */

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
    output2 = 0;
    free(output2);
    
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

static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
	int			p10;

	if ( x == 0.0 )
	{
		*digit = '0';			// digit is always '0'
		*pow10 = 0;
		*remainder = 0.0;
	}
	else
	{
		*pow10 = 0;			// start with 10^0
		while ( x >= 10.0 )		// reduce
		{
			x /= 10.0;		// large values get smaller
			*pow10 += 1;
		}
		while ( x < 1.0 )		// increase
		{
			x *= 10.0;		// small values get larger
			*pow10 -= 1;
		}
		*digit = '0';
		do {				// 10.0 > x >= 1.0
			x -= 1.0;
			*digit += 1;		// digit is always non-'0'zero
		} while ( x >= 1.0 );
		p10 = 0;
		while ( p10 > *pow10 )		// leading digit is now removed from x
		{
			x /= 10;
			p10 -= 1;
		}
		while ( p10 < *pow10 )
		{
			x *= 10;
			p10 += 1;
		}
		*remainder = x;
	}
}

// Improve efficiency by adding more while loops to handle larger powers of 10, e.g. :
// while ( x >= 1e1024 ) { x /= 1e0124; pow10 += 1024; }
// while ( x >= 1e512 ) { x /= 1e512; pow10 += 512; }
// ...
// while ( x >= 10.0 ) { x /= 10.0 ; pow10 += 1; }
// And
// while ( x < 1.0 ) { x *= 10; pow10 -= 1; }
// ...
// while ( x < 1e-512 ) { x *= 1e512; pow10 -= 512; }
// while ( x < 1e-1024 ) { x *= 1e1024; pow10 -= 1024; }

static void
append( char * s, char c )
{
	char		buf[2];

	buf[0] = c;
	buf[1] = '\0';
	strcat( s, buf );
}

union Number {
	int	i;
	float	f;
};

void
floatToASCII( float x, char * output )
{
	char		c;
	int		pow10, p10, plast;
	int		i;
	float		remainder;
	char		exponent[10];
	union Number	a;
	unsigned int	biasedExp;
	unsigned int	mantissa;
	int		sign;



	a.f = x;
	biasedExp = a.i >> 23 & 0x000000ff;
	mantissa = a.i & 0x007fffff;
	sign = a.i >> 31;
	//printf( "BKR x is %g.  biasedExp is %x  mantissa is %08x  sign is %d\n", x,
//		biasedExp, mantissa, sign );
	if ( biasedExp == 0xff )
	{
		if ( mantissa == 0 )
		{
			if ( sign != 0 )
			{
				strcpy( output, "-inf" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
			else
			{
				strcpy( output, "+inf" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
		}
		else
		{
			if ( sign != 0 )
			{
				strcpy( output, "-NaN" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
			else
			{
				strcpy( output, "+NaN" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
		}
	}
	output[0] ='\0';
	if ( x < 0.0 )
	{
		append( output, '-' );
		x = -x;					// make x positive
	}
	get_float_digit( x, &c, &pow10, &remainder );
	append( output, c );
	append( output, '.' );
	x = remainder;
	plast = p10 = pow10;			// pow10 set by get_float_digit()
	for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
	{
		get_float_digit( x, &c, &p10, &remainder );
		if ( (plast - p10) > 1 )
		{
			append( output, '0' );	// fill in zero to next nonzero digit
			plast -= 1;
		}
		else
		{
			append( output, c );
			x = remainder;
			plast = p10;
		}
	}
	if ( pow10 < 0 )		// negative exponent
	{
		exponent[0] = 'e';
		intToASCII( pow10, exponent+1,10,1);
	}
	else if ( pow10 < 10 )		// positive single-digit exponent
	{
		exponent[0] = 'e';
	//	exponent[1] = '+';
		exponent[1] = '0';
		intToASCII( pow10, exponent+2,10,0);
	}
	else				// positive multi-digit exponent
	{
		exponent[0] = 'e';
	//	exponent[1] = '+';
		intToASCII( pow10, exponent+1 ,10,0);
	}
	strcat( output, exponent );
}



int main(int argc, char ** argv){
    if(argc != 3){
        fprintf(stderr, "ERROR: Incorrect number of arguments\n");
        return 0;
    }   
    if(strlen(argv[1]) != 32){
        fprintf(stderr,"ERROR: Input is not a 32 bit size binary number.\n");
        return 0;
    }

    int i;
    for(i = 0; i < 32; i++){
        if(argv[1][i]  != '1' && argv[1][i] != '0'){
            fprintf(stderr,"ERROR: Binary input contains invalid characters.\n");
            //printf("%d\n",i);
            return 0;
        }
    }   


    if(strcmp(argv[2],"float") == 0){
        char * output = malloc(35);
        //int sign = 0;
        //char signchar = 0;
        int x = ASCIIToInt(argv[1],2,0);
        float y = 0;
        memcpy(&y,&x,sizeof(x));
        /*
        if(x < 0){
            sign = 1;
            signchar = '-';
        }*/
        floatToASCII(y,output);
        //strcat(output,"\n");//better to include \n in the formal string
        fprintf(stdout,"%s\n",output);
        free(output);
        //printf("%s\n",output);
        //printf("%d\n", x);


    }
    else if(strcmp(argv[2],"int") == 0){
        char * output = malloc(35);
        int sign = 0;
        char * signchar = malloc(36);
        signchar[0] = 0;
        int x = ASCIIToInt(argv[1],2,0);
        if(x < 0){
            sign = 1;
            signchar[0] = '-';
        }
        

        output = intToASCII(ASCIIToInt(argv[1],2,0),output,10,sign);
        strcat(signchar,output);
        fprintf(stdout,"%s\n", signchar);
        free(output);
        free(signchar);
  //:      printf("%d\n", x);
    }
    else{
        fprintf(stderr,"ERROR: Incorrect output type\n");
    }
    

    return 0; 
}

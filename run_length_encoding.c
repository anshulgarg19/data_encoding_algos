#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_freq( int count,char dest[],int *j)		// to print the freq
{
	char num[50] = { 0 };

	int m = 0,i,rem;					//index of num array
	while( count )
	{
		rem = count % 10;
		count/= 10;
		num[m++] = rem +48;
	}

	//printing num in reverse direction
	for(i= strlen(num)-1; i>=0;i--)
	{
		dest[(*j)++] = num[i];	
	}
}

void encodeRLE(char inputStr[], char destStr[])
{
	int i,count,j;
	char key;
	key = inputStr[0];						//initialisation
	count = 1;		


	for(i=1;i< strlen(inputStr);i++)		
	{
		if( inputStr[i] == key )
			count++;
		else 
		{
			destStr[j++] = key;
			print_freq(count,destStr,&j);
			key = inputStr[i];
			count = 1;
		}
	}

	destStr[j++] = key;
	print_freq(count,destStr,&j);
	destStr[j] = '\0';
}

void decodeRLE(char str[])
{
	char ch;
	int count=0,j;
	int i,div=10,prev=0;
	ch = str[0];
	for(i=1;i< strlen(str);i++)
	{
		if( isdigit(str[i]) )			//str[i] a digit
		{
			count = prev* div + str[i]-48;
			prev = count;
		}
		else{							//not a digit, then print
			for(j=0;j< count;j++)
				printf("%c",ch);
			prev = 0;
			ch = str[i];
		}
	}
	for(j=0;j<count;j++)
		printf("%c",ch);
}

int main( void )
{
	char inputStr[50],destStr[100];				//inputStr stores input string, destStr stores encoded string
	int key,i,count,j=0;

	printf("Enter the string to encode: ");
	scanf("%s",inputStr);

	printf("Encoding using RLE:\n");
	encodeRLE(inputStr, destStr);
	printf("%s\n",destStr);
	printf("Encoding done.\n");	

	printf("Decoding:\n");
	decodeRLE( destStr );
	printf("\n");

	return 0;
}

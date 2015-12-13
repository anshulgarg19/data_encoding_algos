#include<stdio.h>
#include<string.h>

#define STR_SIZE 100
#define VALUE_NUM 128

typedef struct cont{
	double ownfreq;
	double cfp;
	double cfo;
}cont;


double arith_encode( char str[], cont values[] )
{
	int i;
	double l=0,u =1,newu,newl;
	for(i=0;i< strlen(str);i++)	
	{
		newu = l + (u-l)* values[(int)str[i]].cfo;
		newl = l + (u-l)* values[(int)str[i]].cfp;
		l = newl;
		u = newu;
	}
	return u;
}

int main( void )
{
	int i;
	double fin,prev;
	char inputStr[STR_SIZE];
	scanf("%s",inputStr);	

	cont values[VALUE_NUM];			//to save freq and l,u
	int freq[VALUE_NUM] = {0};

	for(i=0;i < strlen(inputStr);i++)		//i
	{
		freq[(int)inputStr[i]]++;				
	}

	prev = 0;					//double prev
	for(i=0;i< VALUE_NUM;i++)
	{
		values[i].ownfreq = (double)freq[i] / strlen(inputStr);
		if( values[i].ownfreq != 0 )
		{
			values[i].cfp = prev;
			values[i].cfo = values[i].cfp + values[i].ownfreq;
			prev = values[i].cfo;
		}
	}

	fin = arith_encode( inputStr , values);	
	printf("value for string is %lf\n",fin);
	return 0;
}

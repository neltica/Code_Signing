#include "cal.h"

BIG_DECIMAL create_BIG_DECIMAL(unsigned char *str, int size)
{
	int i;
	BIG_DECIMAL result;
	result.size=size;

	result.digit = (unsigned char*) malloc (size );

	for(i=0 ; i<size ; i++)
	{
		result.digit[i] = str[size-1-i] - 48;
	}
	return result;
}

void printf_BIG_DECIMAL(BIG_DECIMAL decimal)
{
	int i;

	for(i=decimal.size-1;i>=0;i--)
	{
		printf("%c",decimal.digit[i]+48);
	}
	printf("\n");
}


BIG_DECIMAL big_add(BIG_DECIMAL *A, BIG_DECIMAL *B)
{

}	

BIG_DECIMAL big_min(BIG_DECIMAL *A, BIG_DECIMAL *B)
{

}

BIG_DECIMAL big_div(BIG_DECIMAL *A, BIG_DECIMAL *B)
{

}

BIG_DECIMAL big_mod(BIG_DECIMAL *A, BIG_DECIMAL *B)
{

}

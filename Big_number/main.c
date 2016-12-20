#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "cal.h"

int main(int argc, char * argv[])
{

	BIG_DECIMAL decimal1;
	BIG_DECIMAL decimal2;
	BIG_DECIMAL result,result2,result3,result4,result5;

	int ret;
	char * command1=(char*)malloc(sizeof(char)*100);
	char * command2=(char*)malloc(sizeof(char)*100);

	scanf("%s",command1);
	scanf("%s",command2);

	printf("command1: %s\n",command1);
	printf("command2: %s\n",command2);



	decimal1=create_BIG_DECIMAL( (unsigned char *)command1, strlen(command1) );
	decimal2=create_BIG_DECIMAL( (unsigned char *)command2, strlen(command2) );
	//printf("%d\n",decimal.size);
	printf("decimal1 : ");
	printf_BIG_DECIMAL_struct(decimal1);
	printf("\n");

	printf("decimal2 : ");
	printf_BIG_DECIMAL_struct(decimal2);
	printf("\n");

	result=big_add(&decimal1,&decimal2);

	printf("A+B result : ");
	printf_BIG_DECIMAL_struct(result);	
	printf("\n");

	result=big_min(&decimal1,&decimal2);

	printf("A-B result : ");
	printf_BIG_DECIMAL_struct(result);	
	printf("\n");

	result=big_mul(&decimal1,&decimal2);

	printf("A*B result : ");
	printf_BIG_DECIMAL_struct(result);	
	printf("\n");

	result=big_div(&decimal1,&decimal2);

	printf("A/B result : ");
	printf_BIG_DECIMAL_struct(result);	
	printf("\n");

	result=big_mod(&decimal1,&decimal2);

	printf("A%%B result : ");
	printf_BIG_DECIMAL_struct(result);	
	printf("\n");

	ret=is_Prime_BIG_DECIMAL(&decimal1);
	if(ret==1)
	{
		printf("A is Prime    ");
	}
	else
	{
		printf("A is not Prime    ");
	}

	ret=is_Prime_BIG_DECIMAL(&decimal2);
	if(ret==1)
	{
		printf("B is Prime\n");
	}
	else
	{
		printf("B is not Prime\n");
	}

	printf("Prime bigger than decimal1:");
	result=make_Prime_BIG_DECIMAL(&decimal1);
	printf_BIG_DECIMAL_struct(result);

	printf("\nPrime bigger than decimal2:");
	result=make_Prime_BIG_DECIMAL(&decimal2);
	printf_BIG_DECIMAL_struct(result);


	return 0;
}


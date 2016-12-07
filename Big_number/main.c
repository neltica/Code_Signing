#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cal.h"

int main(int argc, char * argv[])
{
	char * command1=(char*)malloc(sizeof(char)*100);
	char * command2=(char*)malloc(sizeof(char)*100);

	scanf("%s",command1);
	scanf("%s",command2);

	printf("command1: %s\n",command1);
	printf("command2: %s\n",command2);



	BIG_DECIMAL decimal1=create_BIG_DECIMAL( (unsigned char *)command1, strlen(command1) );
	BIG_DECIMAL decimal2=create_BIG_DECIMAL( (unsigned char *)command2, strlen(command2) );
	//printf("%d\n",decimal.size);
	printf("decimal1 : ");
	printf_BIG_DECIMAL_struct(decimal1);
	printf("\n");

	printf("decimal2 : ");
	printf_BIG_DECIMAL_struct(decimal2);
	printf("\n");

	BIG_DECIMAL result=big_add(&decimal1,&decimal2);

	printf("A+B result : ");
	printf_BIG_DECIMAL_struct(result);	
	printf("\n");

	BIG_DECIMAL result2=big_min(&decimal1,&decimal2);

	printf("A-B result : ");
	printf_BIG_DECIMAL_struct(result2);	
	printf("\n");

	BIG_DECIMAL result3=big_mul(&decimal1,&decimal2);

	printf("A*B result : ");
	printf_BIG_DECIMAL_struct(result3);	
	printf("\n");
	return 0;
}


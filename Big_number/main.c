#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cal.h"

int main(int argc, char * argv[])
{
	char * command=(char*)malloc(sizeof(char)*100);

	scanf("%s",command);

	printf("%s\n",command);

	BIG_DECIMAL decimal=create_BIG_DECIMAL( (unsigned char *)"123456789", 10 );

	//printf("%d\n",decimal.size);
	printf_BIG_DECIMAL(decimal);

	return 0;
}


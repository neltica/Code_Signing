#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uchar unsigned char

uchar* big_add(uchar *big_a,uchar *big_b);
uchar* big_min(uchar *big_a, uchar *big_b);
uchar* big_mul(uchar *big_a, uchar *big_b);
uchar* big_div(uchar *big_a, uchar *big_b);
uchar* big_mod(uchar *big_a, uchar *big_b);

int main(int argc, char * argv[])
{
	int i;
	uchar *big_num1,*big_num2;
	int key_size;

	if(argc==2)
	{
		argv[0];
		sscanf(argv[1],"%d",&key_size);
		printf("key_size:%d\n",key_size);
	}
	else
	{
		printf("please input value at least one.\n");
		return 0;
	}

	big_num1=(uchar*)malloc(sizeof(uchar)*key_size);
	big_num2=(uchar*)malloc(sizeof(uchar)*key_size);

	big_num1[127]=248;
	big_num1[126]=15;

	big_num2[127]=255;
	big_num2[126]=15;
	big_num1=big_add(big_num1,big_num2);
	printf("%d %d\n",big_num1[126],big_num1[127]);

	
	return 0;
}

uchar* big_add(uchar *big_a, uchar *big_b)
{
	int i;
	uchar upper=0;
	int add_num=0;

	for(i=127;i>=0;i--)
	{
		add_num=big_a[i]+big_b[i]+upper;

		if(add_num>=256)
		{
			upper=1;
		}
		else
		{
			upper=0;
		}
		big_a[i]=add_num;
	}
	return big_a;
}

uchar* big_min(uchar *big_a, uchar *big_b)
{
	int i;
	uchar lower=0;
	for(i=127;i>=0;i--)
	{
		if(big_a[i]<big_b[i])
		{
			lower=255;
			big_a[i-1]-=1;
		}
		else
		{
			lower=0;
		}
		big_a[i]= (big_a[i]+lower) - big_b[i];
	}
	return big_a;
}

uchar* big_mul(uchar *big_a, uchar *big_b)
{

	return big_a;
}

uchar* big_div(uchar *big_a, uchar *big_b)
{
	return big_a;
}

uchar* big_mod(uchar *big_a, uchar *big_b)
{
	return big_a;
}



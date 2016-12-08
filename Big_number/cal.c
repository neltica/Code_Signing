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
}


void printf_BIG_DECIMAL_struct(BIG_DECIMAL decimal)
{
	int i;

	for(i=decimal.size-1;i>=0;i--)
	{
		printf("%c",decimal.digit[i]+48);
	}
	printf(" %d",decimal.size);
}

int cmp_BIG_DECIMAL(BIG_DECIMAL *A,BIG_DECIMAL *B)
{
	int i;
	if(A->size > B->size)
	{
		return 1;
	}
	else if(A->size < B->size)
	{
		return -1;
	}
	else
	{
		for(i=A->size-1; i>=0; i--)
		{
			if(A->digit[i] > B->digit[i])
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
	}
	return 0;
}

BIG_DECIMAL big_add(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	int i;
	int min,max;
	int tmp;
	BIG_DECIMAL result;
	BIG_DECIMAL *bigger_num;

	bigger_num = (A->size >= B->size ) ? A : B;
	min = (A->size > B->size) ? B->size : A->size;
	max = (A->size > B->size) ? A->size : B->size;
	tmp=0;

	result.digit=(unsigned char*)malloc(max+1);

	for(i=0;i<min;i++)
	{
		result.digit[i] = A->digit[i] + B->digit[i] + tmp;
		if(result.digit[i] > 0x09)
		{
			result.digit[i] %= 0x0A;
			tmp=1;
		}
		else
		{
			tmp=0;
		}
	}

	for(i; i < max; i++)
	{
		result.digit[i] = bigger_num->digit[i] + tmp;
		if(result.digit[i] > 0x09)
		{
			result.digit[i] %= 0x0A;
			tmp=1;
		}
		else
		{
			tmp=0;
		}
	}

	if(tmp)
	{
		result.digit[i]=tmp;
		result.size=max+1;
	}
	else
	{
		result.size=max;
	}
	return result;
}	

BIG_DECIMAL big_min(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	int i;
	int min;
	int max;
	int tmp;
	BIG_DECIMAL result;
	BIG_DECIMAL *bigger_num,*smaller_num;

	i=cmp_BIG_DECIMAL(A,B);
	if(i==1)
	{
		bigger_num=A;
		smaller_num=B;
	}
	else if(i==-1)
	{
		bigger_num=B;
		smaller_num=A;
	}
	else
	{
		result.digit[0]=0;
		result.size=1;
		return result;
	}

	min = (A->size > B->size) ? B->size : A->size;
	max = (A->size > B->size) ? A->size : B->size;

	tmp=0;
	result.digit=(unsigned char*)malloc(max);

	for(i=0;i<min;i++)
	{
		if(bigger_num->digit[i]-tmp >= smaller_num->digit[i])
		{
			result.digit[i] = bigger_num->digit[i]-tmp - smaller_num->digit[i];
			tmp=0;
		}
		else
		{
			result.digit[i] = 10 + (bigger_num->digit[i]-tmp) - smaller_num->digit[i];
			tmp=1;
		}
	}

	for(i; i<max;i++)
	{
		if(bigger_num->digit[i] >= tmp)
		{
			result.digit[i] = bigger_num->digit[i] - tmp;
			tmp = 0;
		}
		else
		{
			result.digit[i] =  bigger_num->digit[i] + 10 - tmp;
			tmp = 1;
		}
	}

	result.size=max;

	while(!result.digit[i-1] && i>1)
	{
		result.size-=1;
		i--;
	}

	return result;

}

BIG_DECIMAL big_mul(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	int i,j;
	int tmp,mul_digit,sum_digit;
	int min,max;
	BIG_DECIMAL result;
	result.size = A->size + B->size;
	result.digit = (unsigned char*) malloc (result.size);

	max = (A->size > B->size) ? A->size : B->size;
	min = (A->size > B->size) ? B->size : A->size;

	for(i=0;i<A->size;i++)
	{
		tmp=0;
		for(j=0;j<B->size;j++)
		{
			mul_digit = (A->digit[i]*B->digit[j])+tmp;
			tmp = mul_digit/0x0A;

			sum_digit= (mul_digit%0x0A + result.digit[i+j]);
			tmp += sum_digit/0x0A;

			result.digit[i+j]=sum_digit%0x0A;
		}
		if(tmp)
		{
			result.digit[i+j]+=tmp;
		}
		//show calculate flow
		printf("%d : ",i);
		printf_BIG_DECIMAL_struct(result);
		printf("\n");
		
	}

	i=result.size;
	while(!result.digit[i-1] && i>1)
	{
		result.size-=1;
		i--;
	}
	return result;
}

BIG_DECIMAL big_div(BIG_DECIMAL *A, BIG_DECIMAL *B)
{

}

BIG_DECIMAL big_mod(BIG_DECIMAL *A, BIG_DECIMAL *B)
{

}

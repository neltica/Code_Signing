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

int cmp_BIG_DECIMAL(BIG_DECIMAL *A,BIG_DECIMAL *B)    //A>B==1,  A<B==-1,  A=B==0
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
			else if(A->digit[i] < B->digit[i])
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

BIG_DECIMAL big_add_digit(BIG_DECIMAL * A,unsigned char digit)
{
	int i;
	int min,max;
	int tmp;
	BIG_DECIMAL result;
	BIG_DECIMAL *bigger_num;

	bigger_num = A;
	max = A->size;
	tmp=0;

	result.digit=(unsigned char*)malloc(max+1);

	result.digit[0]=A->digit[0]+digit;
	if(result.digit[0]>0x09)
	{
		result.digit[0]=result.digit[0]%0x0A;
		tmp=1;
	}
	else
	{
		result.size=max;
		return result;
	}
	for(i=1;i<max;i++)
	{
		result.digit[i]=A->digit[i]+tmp;
		if(result.digit[i]>0x09)
		{
			tmp=1;
			result.digit[i]=result.digit[i]%0x0A;
		}
		else
		{
			result.size=max;
			return result;
		}
	}
	if(tmp)
	{
		result.digit[i]=tmp;
		result.size=max+1;
	}
	else
	{
		result.size=1;
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
		result.digit=(unsigned char*)malloc(1);
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
	memset(result.digit,0,result.size);

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
		/*
		//show calculate flow
		printf("%d : ",i);
		printf_BIG_DECIMAL_struct(result);
		printf("\n");
		*/
		
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
	int i,j;
	int ret;
	int value;
	BIG_DECIMAL result;
	BIG_DECIMAL A_copy, tmp_result;

	if(A->size < B->size)
	{
		result.digit=(unsigned char*)malloc(1);
		result.digit[0]=0;
		result.size=1;
		return result;
	}
	result.digit=(unsigned char *)malloc(A->size-B->size+1);
	result.size=A->size-B->size+1;

	A_copy.digit=(unsigned char *)malloc(A->size);
	A_copy.size=A->size;

	for(i=0;i<A->size;i++)
	{
		A_copy.digit[i]=A->digit[i];
	}
	for(i=A->size-B->size; i>=0;i--)
	{
		tmp_result.digit=&A_copy.digit[i];
		tmp_result.size=A_copy.size-i;
		value=0;
		while(1)
		{
			ret=cmp_BIG_DECIMAL(&tmp_result,B);
			if(ret==0 || ret==1)
			{
				tmp_result=big_min(&tmp_result,B);
				value++;
			}
			else
			{
				break;
			}
		}
		
		while(!tmp_result.digit[tmp_result.size-1] && tmp_result.size>0)
		{
			tmp_result.size-=1;
		}
		A_copy.size=i+tmp_result.size;
		for(j=0;j<tmp_result.size;j++)
		{
			A_copy.digit[i+j]=tmp_result.digit[j];
		}
		result.digit[i]=value;

	}
	while(!result.digit[result.size-1] && result.size>1)
	{
		result.size--;
	}

	free(A_copy.digit);
	return result;
}

BIG_DECIMAL big_mod(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	int i,j;
	int ret;
	BIG_DECIMAL result, tmp_result;
	result.digit=(unsigned char *)malloc(A->size);
	result.size=A->size;

	if(A->size < B->size)
	{
		for(i=0;i<A->size;i++)
		{
			result.digit[i]=A->digit[i];
		}
		result.size=A->size;
		return result;
	}

	for(i=0;i<A->size;i++)
	{
		result.digit[i]=A->digit[i];
	}
	for(i=A->size-B->size; i>=0;i--)
	{
		tmp_result.digit=&result.digit[i];
		tmp_result.size=result.size-i;
		while(1)
		{
			ret=cmp_BIG_DECIMAL(&tmp_result,B);
			if(ret==0 || ret==1)
			{
				tmp_result=big_min(&tmp_result,B);
			}
			else
			{
				break;
			}
		}
		
		while(!tmp_result.digit[tmp_result.size-1] && tmp_result.size>0)
		{
			tmp_result.size-=1;
		}
		result.size=i+tmp_result.size;
		for(j=0;j<tmp_result.size;j++)
		{
			result.digit[i+j]=tmp_result.digit[j];
		}

	}

	return result;
}


int is_Prime_BIG_DECIMAL(BIG_DECIMAL *A)
{
	BIG_DECIMAL divisor;
	BIG_DECIMAL div_result;
	BIG_DECIMAL result;
	unsigned char * tmp_digit;
	int i;

	if(A->digit[0]==0x02 && A->size==1)
	{
		return 1;
	}
	else if(A->size==1 && A->digit[0]==0x01)
	{
		return 0;
	}
	else if( (A->digit[0]^0x01)&0x01)
	{
		return 0;
	}

	divisor=create_BIG_DECIMAL( (unsigned char*)"3",1 );

	div_result=big_div(A,&divisor);

	while(cmp_BIG_DECIMAL(&div_result,&divisor)==1)
	{
		result=big_mod(A,&divisor);

		if(result.size==1 && result.digit[0]==0)
		{
			free(result.digit);
			free(divisor.digit);
			free(div_result.digit);
			return 0;
		}

		free(result.digit);

		tmp_digit=divisor.digit;
		divisor=big_add_digit(&divisor,0x02);
		free(tmp_digit);

		tmp_digit=div_result.digit;
		div_result=big_div(A,&divisor);
		free(tmp_digit);

	}

	free(divisor.digit);
	free(div_result.digit);

	return 1;
}
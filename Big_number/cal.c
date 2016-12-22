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

BIG_BINARY create_BIG_BINARY(unsigned char *str, int size)
{
	int i;
	BIG_BINARY result;
	result.size=size;

	result.byte = (unsigned char*) malloc (size );

	for(i=0 ; i<size ; i++)
	{
		result.byte[i] = str[size-1-i];
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

void printf_BIG_BINARY(BIG_BINARY binary)
{
	int i,j;
	unsigned char flag;

	for(i=binary.size-1;i>=0;i--)
	{
		flag=0x80;

		for(j=0;j<8;j++)
		{
			if(binary.byte[i]&flag)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
			flag>>=1;
		}
		printf(" ");
	}
}
void printf_BIG_BINARY_struct(BIG_BINARY binary)
{
	int i,j;
	unsigned char flag;

	for(i=binary.size-1;i>=0;i--)
	{
		flag=0x80;

		for(j=0;j<8;j++)
		{
			if(binary.byte[i]&flag)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
			flag>>=1;
		}
		printf(" ");
	}
	printf(" %d",binary.size);
}

void printf_Factorize(BIG_DECIMAL *A)
{
	BIG_DECIMAL copy_A,result,one;
	int i;
	unsigned char *ptrForFree;

	copy_A.digit=(unsigned char *)malloc(A->size);
	for(i=0;i<A->size;i++)
	{
		copy_A.digit[i]=A->digit[i];
	}
	copy_A.size=A->size;

	one=create_BIG_DECIMAL((unsigned char*)"1",1);
	while(cmp_BIG_DECIMAL(&copy_A,&one)!=0)
	{
		result=factorize(&copy_A);
		printf_BIG_DECIMAL_struct(result);
		printf("\n");
		ptrForFree=copy_A.digit;
		copy_A=big_div(&copy_A,&result);
		free(ptrForFree);
		free(result.digit);
	}
	free(copy_A.digit);
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
	for(i=0;i<A->size;i++)
	{
		result.digit[i]=A->digit[i];
	}
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

BIG_DECIMAL big_mul_digit(BIG_DECIMAL *A,unsigned char digit)
{
	int i;
	BIG_DECIMAL result;
	unsigned char tmp;
	unsigned int size=A->size+1;

	result.digit=(unsigned char *)malloc(size);
	tmp=0;

	for(i=0;i<A->size;i++)
	{
		result.digit[i]=(A->digit[i]*digit)+tmp;

		tmp=result.digit[i]/0x0A;
		result.digit[i]%=0x0A;
	}

	if(tmp)
	{
		result.digit[i]=tmp;
		result.size=size;
	}
	else
	{
		result.size=A->size;
	}
	return result;
}

BIG_DECIMAL big_mul_expo(BIG_DECIMAL *A,BIG_DECIMAL *B)
{
	int i,j,position;
	unsigned char flag,*ptrForFree;
	BIG_DECIMAL result,tmp;

	BIG_BINARY binaryB=decimal_To_binary(B);

	result=create_BIG_DECIMAL((unsigned char*)"1",1);
	tmp=big_mul_digit(A,1);

	position=8*(binaryB.size-1);

	j=8;
	flag=0x80;

	for(i=0;i<8;i++)
	{
		if(binaryB.byte[binaryB.size-1]&flag)
		{
			position+=j;
			break;
		}
		j--;
		flag>>=1;
	}

	for(i=0;i<binaryB.size;i++)
	{
		flag=0x01;

		for(j=0;j<8;j++)
		{
			if(binaryB.byte[i]&flag)
			{
				ptrForFree=result.digit;
				result=big_mul(&result,&tmp);
				free(ptrForFree);
			}

			position--;
			if(position==0)
			{
				break;
			}

			ptrForFree=tmp.digit;
			tmp=big_mul(&tmp,&tmp);
			free(ptrForFree);

			flag<<=1;
		}
	}
	return result;
}

BIG_DECIMAL big_div(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	int i,j;
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
			if(cmp_BIG_DECIMAL(&tmp_result,B)!=-1)
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
		
		/*while(!tmp_result.digit[tmp_result.size-1] && tmp_result.size>0)
		{
			tmp_result.size-=1;
		}*/
		result.size=i+tmp_result.size;
		for(j=0;j<tmp_result.size;j++)
		{
			result.digit[i+j]=tmp_result.digit[j];
		}

	}

	return result;
}

BIG_DECIMAL big_mod_expo(BIG_DECIMAL *A,BIG_DECIMAL *E,BIG_DECIMAL *M)
{
	int i,j,position;
	unsigned char flag,*ptrForFree;
	BIG_DECIMAL result,tmp;

	BIG_BINARY binaryE=decimal_To_binary(E);

	result=create_BIG_DECIMAL((unsigned char*)"1",1);
	tmp=big_mul_digit(A,0x01);

	position= 8*(binaryE.size-1);
	j=8;
	flag=0x80;

	for(i=0;i<8;i++)
	{
		if(binaryE.byte[binaryE.size-1]&flag)
		{
			position+=j;
			break;
		}

		j--;
		flag>>=1;
	}

	for(i=0;i<binaryE.size;i++)
	{
		flag=0x01;

		for(j=0;j<8;j++)
		{
			if(binaryE.byte[i]&flag)
			{
				ptrForFree=result.digit;
				result=big_mul(&result,&tmp);
				free(ptrForFree);

				ptrForFree=result.digit;
				result=big_mod(&result,M);
				free(ptrForFree);
			}
			position--;
			if(position==0)
			{
				break;
			}

			ptrForFree=tmp.digit;
			tmp=big_mul(&tmp,&tmp);
			free(ptrForFree);

			ptrForFree=tmp.digit;
			tmp=big_mod(&tmp,M);
			free(ptrForFree);

			flag<<=1;
		}
	}

	return result;
}


int is_Prime_BIG_DECIMAL(BIG_DECIMAL *A)  // not prime==0, prime==1
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



BIG_DECIMAL make_Prime_BIG_DECIMAL(BIG_DECIMAL *A)
{
	BIG_DECIMAL result;

	result=*A;

	for(;;)
	{
		if(is_Prime_BIG_DECIMAL(&result))
		{
			break;
		}
		else
		{
			result=big_add_digit(&result,0x01);
		}
	}

	return result;
}

BIG_DECIMAL make_Prime_BIG_DECIMAL_digit(int digit)   //if digit=32, then search prime is bigger than 2^32.
{
	BIG_DECIMAL result;
	int i;
	result=create_BIG_DECIMAL((unsigned char*)"2",1);
	for(i=0;i<digit;i++)
	{
		result=big_mul(&result,&result);
	}

	for(;;)
	{
		if(is_Prime_BIG_DECIMAL(&result))
		{
			break;
		}
		else
		{
			result=big_add_digit(&result,0x01);
		}
	}

	return result;
}

BIG_DECIMAL factorize(BIG_DECIMAL *A)
{
	BIG_DECIMAL denominator,max,result;
	unsigned char *ptrForFree;

	if((A->digit[0]^0x01)&0x01)
	{
		return create_BIG_DECIMAL((unsigned char*)"2",1);
	}

	denominator=create_BIG_DECIMAL((unsigned char*)"3",1);

	max=big_div(A,&denominator);

	while(cmp_BIG_DECIMAL(&max,&denominator)!=-1)
	{
		result=big_mod(A,&denominator);
		if(result.size==1 && result.digit[0]==0)
		{
			free(max.digit);
			return denominator;
		}

		free(result.digit);

		ptrForFree=denominator.digit;

		denominator=big_add_digit(&denominator,0x02);
		free(ptrForFree);

		ptrForFree=max.digit;
		max=big_div(A,&denominator);
		free(ptrForFree);
	}
	free(denominator.digit);
	free(max.digit);

	denominator=big_mul_digit(A,1);

	return denominator;
}

BIG_DECIMAL binary_To_decimal(BIG_BINARY *binary)
{
	int i,j;
	unsigned char flag,*ptrForFree;

	BIG_DECIMAL decimal, tmp;

	decimal=create_BIG_DECIMAL((unsigned char *)"0",1);
	tmp=create_BIG_DECIMAL((unsigned char *)"1",1);

	for(i=0;i<binary->size;i++)
	{
		flag=0x01;
		for(j=0;j<8;j++)
		{
			if(binary->byte[i]&flag)
			{
				ptrForFree=decimal.digit;
				decimal=big_add(&decimal,&tmp);
				free(ptrForFree);
			}

			flag<<=1;

			ptrForFree=tmp.digit;
			tmp=big_mul_digit(&tmp,0x02);
			free(ptrForFree);
		}
	}

	return decimal;
}

BIG_BINARY decimal_To_binary(BIG_DECIMAL *decimal)
{
	int i,j,position;
	BIG_BINARY binary;
	BIG_DECIMAL numerator,denominator,remainder,zero;
	void *ptrDigit;
	unsigned char tmpMultiply;

	binary.byte=(unsigned char*)malloc((int)(decimal->size/2)+1);
	numerator.digit=(unsigned char*)malloc(decimal->size);
	numerator.size=decimal->size;
	for(i=0;i<numerator.size;i++)
	{
		numerator.digit[i]=decimal->digit[i];
	}

	zero=create_BIG_DECIMAL((unsigned char*)"0",1);
	denominator=create_BIG_DECIMAL((unsigned char*)"256",3);

	for(position=0;;position++)
	{
		remainder=big_mod(&numerator,&denominator);

		ptrDigit=(void*)numerator.digit;
		numerator=big_div(&numerator,&denominator);
		free(ptrDigit);

		binary.byte[position]=0x00;

		for(i=0;i<remainder.size;i++)
		{
			tmpMultiply=1;
			for(j=0;j<i;j++)
			{
				tmpMultiply*=10;
			}
			binary.byte[position]+=remainder.digit[i]*tmpMultiply;
		}
		if(cmp_BIG_DECIMAL(&numerator,&zero)==0)
		{
			break;
		}
	}

	binary.size=position+1;
	free(numerator.digit);
	free(denominator.digit);
	free(remainder.digit);
	free(zero.digit);

	return binary;
}
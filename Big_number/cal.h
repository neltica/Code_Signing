#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BIG_DECIMAL
{
	unsigned char *digit;
	unsigned int size;
}BIG_DECIMAL;


BIG_DECIMAL create_BIG_DECIMAL(unsigned char *str, int size);
void printf_BIG_DECIMAL(BIG_DECIMAL decimal);
void printf_BIG_DECIMAL_struct(BIG_DECIMAL decimal);
int cmp_BIG_DECIMAL(BIG_DECIMAL *A, BIG_DECIMAL *B);
int is_Prime_BIG_DECIMAL(BIG_DECIMAL *A);
BIG_DECIMAL big_add(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_add_digit(BIG_DECIMAL * A,unsigned char digit);
BIG_DECIMAL big_min(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_mul(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_div(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_mod(BIG_DECIMAL *A,BIG_DECIMAL *B);


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BIG_DECIMAL
{
	unsigned char *digit;
	unsigned int size;
}BIG_DECIMAL;

typedef struct BIG_BINARY
{
	unsigned char *byte;
	unsigned int size;
}BIG_BINARY;

BIG_DECIMAL create_BIG_DECIMAL(unsigned char *str, int size);
BIG_BINARY create_BIG_BINARY(unsigned char *str, int size);
void printf_BIG_DECIMAL(BIG_DECIMAL decimal);
void printf_BIG_DECIMAL_struct(BIG_DECIMAL decimal);
void printf_BIG_BINARY(BIG_BINARY binary);
void printf_BIG_BINARY_struct(BIG_BINARY binary);
int cmp_BIG_DECIMAL(BIG_DECIMAL *A, BIG_DECIMAL *B);
int is_Prime_BIG_DECIMAL(BIG_DECIMAL *A);
BIG_DECIMAL big_add(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_add_digit(BIG_DECIMAL *A,unsigned char digit);
BIG_DECIMAL big_min(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_mul(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_mul_digit(BIG_DECIMAL *A,unsigned char digit);
BIG_DECIMAL big_mul_expo(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_div(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_mod(BIG_DECIMAL *A,BIG_DECIMAL *B);
BIG_DECIMAL big_mod_expo(BIG_DECIMAL *A,BIG_DECIMAL *E,BIG_DECIMAL *M);
BIG_DECIMAL make_Prime_BIG_DECIMAL(BIG_DECIMAL *A);
BIG_DECIMAL make_Prime_BIG_DECIMAL_digit(int digit);
BIG_DECIMAL binary_To_decimal(BIG_BINARY *binary);
BIG_BINARY decimal_To_binary(BIG_DECIMAL *decimal);

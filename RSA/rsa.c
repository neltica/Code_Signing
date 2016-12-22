#include "rsa.h"

BIG_DECIMAL make_RSA_PublicKey(BIG_DECIMAL *p,BIG_DECIMAL *q)
{
	return big_mul(p,q);
}

BIG_DECIMAL make_RSA_PrivateKey(BIG_DECIMAL *p, BIG_DECIMAL *q, BIG_DECIMAL *e)
{
	BIG_DECIMAL secretKey,tmp,n,one;
	unsigned char *ptrForFree;

	secretKey=create_BIG_DECIMAL((unsigned char*)"1",1);
	one=create_BIG_DECIMAL((unsigned char*)"1",1);

	n=big_mul(&big_min_digit(p,1),&big_min_digit(q,1));
}
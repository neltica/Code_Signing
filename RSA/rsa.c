#include "rsa.h"

BIG_DECIMAL make_RSA_PublicKey(BIG_DECIMAL *p,BIG_DECIMAL *q)
{
	return big_mul(p,q);
}

BIG_DECIMAL make_RSA_PrivateKey(BIG_DECIMAL *p, BIG_DECIMAL *q, BIG_DECIMAL *e)
{
	BIG_DECIMAL privateKey,tmp,n,one;
	unsigned char *ptrForFree;
	BIG_DECIMAL p_min_digit_result,q_min_digit_result;

	privateKey=create_BIG_DECIMAL((unsigned char*)"1",1);
	one=create_BIG_DECIMAL((unsigned char*)"1",1);

	p_min_digit_result=big_min_digit(p,1);
	q_min_digit_result=big_min_digit(q,1);
	n=big_mul(&p_min_digit_result, &q_min_digit_result);

	for(;;)
	{
		tmp=big_mul(e,&privateKey);

		ptrForFree=tmp.digit;
		tmp=big_mod(&tmp,&n);
		free(ptrForFree);

		if(cmp_BIG_DECIMAL(&tmp,&one)==0)
		{
			break;
		}

		ptrForFree=privateKey.digit;
		privateKey=big_add_digit(&privateKey,0x01);
		free(ptrForFree);
		free(tmp.digit);
	}

	return privateKey;
}
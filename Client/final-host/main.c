#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "rsa.h"


#define TOOL_NAME "Signing_Tool"
#define CREATE_KEYS 1
#define VERIFY_SIGNATURE 2
#define MAKE_SIGNATURE 3
#define PRIME_SOURCE_FILE "primes.txt"


void create_keys(char *priv_name, char *pub_name)
{
	struct public_key_class pub[1];
  	struct private_key_class priv[1];
	FILE *priv_file,*pub_file;
	int ret;

	printf("================\n");
	printf("Genkey start\n");
	printf("================\n");

	priv_file=fopen(priv_name,"wb");
	pub_file=fopen(pub_name,"wb");

	rsa_gen_keys(pub, priv, PRIME_SOURCE_FILE);
	while((ret=check_rsa_key(priv,pub,SHA_DIGEST_LENGTH))!=0)
	{
		rsa_gen_keys(pub, priv, PRIME_SOURCE_FILE);
	}
	printf("Private Key:\nModulus: %lld\nExponent: %lld\n", (long long)priv->modulus, (long long) priv->exponent);
	printf("Public Key:\nModulus: %lld\nExponent: %lld\n", (long long)pub->modulus, (long long) pub->exponent);

	fprintf(priv_file,"%lld %lld",(long long)priv->modulus, (long long)priv->exponent);
	fprintf(pub_file,"%lld %lld",(long long)pub->modulus, (long long)pub->exponent);
	fclose(priv_file);
	fclose(pub_file);
	printf("================\n");
	printf("Genkey end\n");
	printf("================\n");
}


long long* rsa_encrypt_sha1(char *priv_name, unsigned char *sha1_message)
{
	long long *encrypted;
  	struct private_key_class priv[1];
	FILE *in_file, *priv_file;
	int i;

	printf("================\n");
	printf("RSA_encrypt start\n");
	printf("================\n");

	priv_file=fopen(priv_name,"rb");
	fscanf(priv_file,"%lld %lld",&priv->modulus,&priv->exponent);
	fclose(priv_file);

	printf("Private Key:\n Modulus: %lld\n Exponent: %lld\n", (long long)priv->modulus, (long long) priv->exponent);
	printf("Original:\n");
	for(i=0; i < SHA_DIGEST_LENGTH; i++)
	{
		printf("%02x", sha1_message[i]);
	}  
	printf("\n");
	printf("encrypt start\n");
	encrypted = rsa_encrypt(sha1_message, SHA_DIGEST_LENGTH, priv);
	if (!encrypted)
	{
		fprintf(stderr, "Error in encryption!\n");
		return;
	}
	printf("Encrypted:\n");
	for(i=0; i < SHA_DIGEST_LENGTH; i++)
	{
		printf("%lld\n", (long long)encrypted[i]);
	}  
	printf("================\n");
	printf("RSA_encrypt end\n");
	printf("================\n");
	return encrypted;
}

char* rsa_decrypt_sha1(char *pub_name, char *in_name)
{
	char *decrypted;
	struct public_key_class pub[1];
	FILE *in_file, *pub_file;

	long long *message;
	int i;

	printf("================\n");
	printf("RSA_decrypt start\n");
	printf("================\n");

	in_file=fopen(in_name,"rb");
	pub_file=fopen(pub_name,"rb");

	fscanf(in_file,"%lld %lld",&pub->modulus,&pub->exponent);
	message=(long long*)malloc(sizeof(long long)*SHA_DIGEST_LENGTH*2);
	for(i=0;i<SHA_DIGEST_LENGTH*2;i++)
	{
		fscanf(in_file,"%lld",&((long long*)message)[i]);
	}
	fclose(pub_file);
	fclose(in_file);

	printf("Public Key:\n Modulus: %lld\n Exponent: %lld\n", (long long)pub->modulus, (long long) pub->exponent);
	printf("Original:\n");
	for(i=0; i < SHA_DIGEST_LENGTH*2; i++)
	{
		printf("%lld", ((long long*)message)[i]);
	}  
	printf("\n");
	printf("decrypt start\n");
	decrypted = rsa_decrypt((long long *)message, 8*SHA_DIGEST_LENGTH*2, pub);
	if (!decrypted)
	{
		fprintf(stderr, "Error in decryption!\n");
		return NULL;
	}
	printf("Decrypted:\n");
	for(i=0; i < SHA_DIGEST_LENGTH*2; i++)
	{
		printf("%c", (char)decrypted[i]);
	}


	printf("================\n");
	printf("RSA_decrypt end\n");
	printf("================\n");
	return decrypted;
}

unsigned char *sha1_encrypt(char * argv)
{
	FILE * file;
	char file_name[256];
	//int file_no;
	//struct stat file_info;

	char *ret;
	int i,counting_file_size;

	size_t read_size=0;
	SHA_CTX sha1; 
	unsigned char *sha1_str;
	char *str;

	printf("================\n");
	printf("SHA1 encrypt start\n");
	printf("================\n");
	
	strcpy(file_name,argv);
	str=(char*)malloc(sizeof(char)*SHA_DIGEST_LENGTH); //원본 메시지
	sha1_str=(unsigned char*)malloc(sizeof(unsigned char)*SHA_DIGEST_LENGTH); //원본 메시지

	file=fopen(file_name,"rb");
	//file_no=fileno(file);
	//fstat(file_no,&file_info);

	SHA1_Init(&sha1); 
	counting_file_size=0;
	i=0;
	while( (read_size=fread(str,1,SHA_DIGEST_LENGTH,file)) >0 )
	{
		//printf("%d\n",read_size);
		counting_file_size+=read_size;
		/*
		printf("%d: %d: ",count,strlen(str));
		count++;
		printf("\n========================================\n");
		for(i=0;read_size;i++)
		{
			if(str[i]=='\r')
			{
				printf("CL ");
			}
			else if(str[i]=='\n')
			{
				printf("NL ");
			} 
			else
			{
				printf("%c ",str[i]);
			}
		}
		printf("\n========================================\n");
		*/
		printf("%d:%d %d\n",i,read_size,counting_file_size);
		i++;
		SHA1_Update(&sha1, str, read_size);
	}
	SHA1_Final(sha1_str, &sha1);
	fclose(file);
	printf("digest length:%d\n",SHA_DIGEST_LENGTH);
	printf("input file name:%s\n",file_name);
	//printf("input file size:%ld\n",file_info.st_size);
	printf("read file size:%d\n",counting_file_size);
	ret=strrchr(file_name,'.');
	*ret=0;
	strcat(file_name,".sha1");
	printf("output file name:%s\n",file_name);

	file=fopen(file_name,"wb");
	printf("sha1 result:");
	for(i=0;i<SHA_DIGEST_LENGTH;i++)
	{

      		printf("%02x",sha1_str[i]);
	}
	printf("\n");
	fprintf(file,"SHA1 RESULT(02x)== ");
	for(i=0;i<SHA_DIGEST_LENGTH;i++)
	{
      		fprintf(file,"%02x",sha1_str[i]);
	}
	fclose(file);

	printf("================\n");
	printf("SHA1 encrypt end\n");
	printf("================\n");
	return sha1_str;
}

void print_helper()
{
	printf("usage:\n");
	printf("./%s genkey -priv private_key_name -pub public_key_name\n",TOOL_NAME);
	printf("./%s sign -input input_file_name -output output_file_name -priv private_key_name\n",TOOL_NAME);
	printf("./%s verify -input input_file_name -output output_file_name -pub public_key_name\n",TOOL_NAME);
}

int check_command_error(int *mode,int argc, char * argv[])
{
	int i;
	int flag=1;

	if(argc==8 || argc==6)
	{
		flag=0;
	}

	flag=1;
	if( strcmp(argv[1],"verify")==0 )
	{
		*mode=VERIFY_SIGNATURE;
		flag=0;
	}
	else if( strcmp(argv[1],"genkey")==0 )
	{
		*mode=CREATE_KEYS;
		flag=0;
	}
	else if( strcmp(argv[1],"sign")==0 )
	{
		*mode=MAKE_SIGNATURE;
		flag=0;
	}

	flag=1;
	for(i=0;i<argc;i++)
	{
		if( strcmp(argv[i],"-output")==0 && argc==8)
		{
			flag=0;
		}
		else if(strcmp(argv[i],"-output")!=0 && argc==6 )
		{
			flag=0;
		}
	}

	return flag;
}

int main(int argc, char* argv[])
{
	int i,read_size;
	FILE *out_file,*in_file;
	char **file_names;
	unsigned char* sha1_result;
	int mode=0;

	int file_no;
	struct stat file_info;

	long long *rsa_encrypted;
	char *str;

	str=(char*)malloc(sizeof(char)*SHA_DIGEST_LENGTH); //원본 메시지
	
	if(check_command_error(&mode,argc,argv)==0)
	{

		file_names=(char**)malloc(sizeof(char*)*4);	
	}
	else
	{
		printf("command error\n");
		print_helper();
		return 0;
	}

	for(i=2;i<argc;i++)
	{
		if(strcmp(argv[i],"-input")==0)
		{
			file_names[0]=argv[i+1];
			i++;
		}
		else if(strcmp(argv[i],"-output")==0)
		{
			file_names[3]=argv[i+1];
			i++;
		}
		else if(strcmp(argv[i],"-priv")==0)
		{
			file_names[1]=argv[i+1];
			i++;
		}
		else if(strcmp(argv[i],"-pub")==0)
		{
			file_names[2]=argv[i+1];
			i++;
		}
		else
		{
			printf("option command error\n");
			return 0;
		}
	}

	printf("mode:%d |priv_key_filename:%s | pub_key_filename:%s | input_filename:%s | output_filename:%s\n",mode,file_names[1],file_names[2],file_names[0],file_names[3]);
	switch(mode)
	{
		case CREATE_KEYS:
		create_keys(file_names[1],file_names[2]);
		break;

		case VERIFY_SIGNATURE:
		rsa_decrypt_sha1(file_names[2], file_names[0]);
		break;

		case MAKE_SIGNATURE:
		sha1_result=sha1_encrypt(file_names[0]);
		printf("SHA1 RESULT:\n");
		for(i=0;i<SHA_DIGEST_LENGTH;i++)
		{
			printf("%c",sha1_result[i]);
		}
		printf("\n");
		rsa_encrypted=rsa_encrypt_sha1(file_names[1], sha1_result);


		out_file=fopen(file_names[3],"wb");
		in_file=fopen(file_names[0],"rb");
		file_no=fileno(in_file);
		fstat(file_no,&file_info);
		printf("RSA_ENCRYPTED RESULT:\n");
		for(i=0;i<SHA_DIGEST_LENGTH;i++)
		{
			printf("%lld\n",rsa_encrypted[i]);
			fprintf(out_file,"%lld\n",rsa_encrypted[i]);
		}
		fprintf(out_file,"%ld\n",file_info.st_size);
		while( (read_size=fread(str,1,SHA_DIGEST_LENGTH,in_file)) >0 )
		{
			fwrite(str,1,read_size,out_file);
		}

		free(sha1_result);
		free(rsa_encrypted);
		fclose(out_file);
		fclose(in_file);
		break;
	}
free(file_names);
free(str);
	return 0;
}

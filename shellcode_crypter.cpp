#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "aes_sources/aes_crypter.h"


int main(int argc, char const *argv[])
{

	//aes_init();
	//aes_encrypt_ctx cx[1];

	char * string_to_enc = (char *)malloc( 10000 );
	char * target_key_char = (char *)malloc( 50 );
	unsigned char * target_string = (unsigned char *)malloc( 10000 );
	unsigned char * target_key = (unsigned char *)malloc( 50 );

	//memset(target_string,0, 10000 );
	//memset(target_key,0, 50 );

	for(int i=1;i<argc;i++)
	{
		if( strcmp( argv[i],"--target_key" ) == 0 )
		{
			strcpy(target_key_char,argv[i+1]);
			i++;
		}
	}

	FILE * fp = fopen("shellcode_enc.txt","r");

	fread(string_to_enc,sizeof(char),10000,fp);

	//printf("%s\n", string_to_enc);

	//for(int i=0;i<strlen(string_to_enc);i++) target_string[i] = string_to_enc[i];
	for(int i=0;i<strlen(target_key_char);i++) target_key[i] = target_key_char[i];
	target_key[ strlen(target_key_char) ] = 0;

	//printf("%d\n", strlen(target_key_char) );

	//printf("%s\n", string_to_enc);
	
	unsigned int string_length = aes_crypter::encrypt_string( string_to_enc, target_key, target_string );
	strcpy(string_to_enc,"");

	aes_crypter::unsigned_to_string( target_string,string_length,string_to_enc );

	printf("%d %s\n", string_length, string_to_enc);

	//free( string_to_enc );
	//free( target_key_char );
	//free( target_key );
	//free( target_string );

	fclose(fp);

	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "aes-master-2/aescpp.h"

int main(int argc, char const *argv[])
{	
	//aes_init();
	aes_encrypt_ctx cx[1];

	unsigned char * plain = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );
	unsigned char * encrypted_message = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );
	unsigned char * key = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );
	unsigned char * plain_2 = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );

	plain_2[0] = 0;

	char * plain_text = (char *)malloc( 1000 );
	char * encrypted_message_text = (char *)malloc( 1000 );
	char * key_text = (char *)malloc( 1000 );

	strcpy(plain_text,"mama are mer");
	strcpy(key_text,"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");
	strcpy(encrypted_message_text,"");

	for(int i=0;i<strlen(plain_text);i++) plain[i] = plain_text[i];
	for(int i=0;i<strlen(key_text);i++) key[i] = key_text[i];

	aes_encrypt_key256(key, cx);
	aes_encrypt(plain, encrypted_message, cx);

	aes_decrypt_key256(key, cx);
	aes_decrypt(encrypted_message, plain_2, cx);

	printf("%s\n", plain_2);


	free(encrypted_message);

	return 0;
}
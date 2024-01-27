#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "aes_crypter.h"

int main(int argc, char const *argv[])
{	
	//aes_init();
	aes_encrypt_ctx cx[1];

	unsigned char * plain = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );
	unsigned char * encrypted_message = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );
	unsigned char * key = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );
	unsigned char * plain_2 = (unsigned char *)malloc( 1000 * sizeof(unsigned char) );

	unsigned int encrypted_message_length = 0;

	plain_2[0] = 0;

	char * plain_text = (char *)malloc( 1000 );
	char * encrypted_message_text = (char *)malloc( 1000 );
	char * key_text = (char *)malloc( 1000 );

	strcpy(plain_text,"mama are mer");
	strcpy(key_text,"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");
	strcpy(encrypted_message_text,"");

	


	free(encrypted_message);

	return 0;
}
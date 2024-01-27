#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "aes_crypter.h"

unsigned int aes_crypter::encrypt_string( char * target_string, unsigned char * key ,unsigned char * target_buffer )
{

	aes_encrypt_ctx cx[1];

	//target_buffer = (unsigned char *)realloc(target_buffer, strlen( target_string ) + 16 );

	aes_encrypt_key256(key, cx);

	unsigned int div_cnt = strlen( target_string ) / 16 ;
	if( strlen( target_string ) % 16 > 0 ) div_cnt++;

	//adding padding

	int padding_len = 16 - ( strlen( target_string ) % 16 );

	for(int i=0;i<padding_len;i++) strcat( target_string, " " );

	//

	//printf("%d %d\n", div_cnt, strlen(target_string) );

	for(int i=0,j=0; i < div_cnt; i++, j += 16)
	{
		//printf("%d %d\n", i, j);
		unsigned char plain_message_buffer[17] = {0};
		unsigned char encrypted_message_buffer[17] = {0};

		int l = 0;

		for(int q = j,w = 0;q < j + 16 /*&& target_string[q] != 0*/; q++, w++, l++)
		{
			//printf("%c", target_string[q]);
			plain_message_buffer[w] = target_string[q];
		}

		plain_message_buffer[l] = '\0';

		aes_encrypt(plain_message_buffer, encrypted_message_buffer, cx);

		for(int q = j,w = 0;q < j + 16 /*&& target_string[q] != 0*/; q++, w++)
		{
			//printf("%c", target_string[q]);
			target_buffer[q] = encrypted_message_buffer[w];
		}

		//printf("\n");

	}

	//printf("%s %s\n", target_string, target_buffer);

	return strlen( target_string );

}

void aes_crypter::decrypt_string( unsigned char * target_string, unsigned int target_string_length, unsigned char * key , char * target_buffer )
{

	aes_encrypt_ctx cx[1];

	int target_string_len = target_string_length;
	//while( target_string[target_string_len] != 0 ) target_string_len++;

	//target_buffer = (char *)realloc(target_buffer, target_string_len + 16 );

	aes_decrypt_key256(key, cx);

	unsigned int div_cnt = target_string_len / 16 ;
	if( target_string_len % 16 > 0 ) div_cnt++;

	//printf("%d %d\n", div_cnt, target_string_len );
	for(int i=0,j=0; i < div_cnt; i++, j += 16)
	{

		unsigned char plain_message_buffer[17] = {0};
		unsigned char encrypted_message_buffer[17] = {0};

		int l = 0;

		for(int q = j,w = 0;q < j + 16 && q < target_string_len; q++, w++, l++)
		{
			//printf("%c", target_string[q]);
			encrypted_message_buffer[w] = target_string[q];
		}

		encrypted_message_buffer[l] = '\0';

		aes_decrypt(encrypted_message_buffer, plain_message_buffer, cx);

		//printf("%s\n", plain_message_buffer);

		for(int q = j,w = 0;q < j + 16 && q < target_string_len; q++, w++)
		{
			//printf("%c", target_string[q]);
			target_buffer[q] = plain_message_buffer[w];
		}

		//printf("\n");

	}

	//eliminate padding

	int pad_cnt = target_string_length - 1;

	while( target_buffer[ pad_cnt ] == ' ' ) pad_cnt--;

	target_buffer[ pad_cnt+1 ] = '\0';

	//printf("%s %s c\n", target_string, target_buffer);

}

void aes_crypter::generate_random_key( unsigned char * key, unsigned short int nr_of_bytes )
{

	int high,low;
	high = 254;
	low = 1;
	for (int i = 0; i < nr_of_bytes; i++)
	{
		int random_nr = low + ( rand() % (high - low) );
		key[i] = random_nr;
		//printf("%d ", random_nr);
		printf("%d\n", key[i]);
	}

	printf("\n");

}

void aes_crypter::seed_init()
{

	srand((unsigned) time(0));

}

void aes_crypter::unsigned_to_string(unsigned char * source, int source_len, char * target_buffer)
{

	strcpy(target_buffer,"");
	for(int i=0;i<source_len;i++)
	{
		char sm_buff[3];
		sprintf(sm_buff,"%02x", source[i]);
		strcat(target_buffer,sm_buff);
	}

}

void aes_crypter::string_to_unsigned(char * source, unsigned char * target_buffer)
{

	memset( target_buffer,0, ( strlen(source) / 2 ) + 1 );
	int j = 0;
	for(int i=0;i<strlen(source);i += 2,j++)
	{
		char sm_buff[3];
		sm_buff[0] = source[i];
		sm_buff[1] = source[i+1];
		target_buffer[j] = (int)strtol(sm_buff,NULL,16);
		//printf("%d ", target_buffer[j]);
	}

	target_buffer[j] = 0;

}

void aes_crypter::char_array_to_unsigned(char * source, unsigned char * target_buffer, int len)
{

	int i;
	int string_length = len;
	if(string_length == 0) string_length = strlen(source);
	for(i=0;i<string_length;i++) target_buffer[i] = source[i];
	target_buffer[i] = 0;

}

void aes_crypter::unsigned_array_to_char(unsigned char * source, char * target_buffer, int len)
{

	int i;
	for(i=0;i<len;i++) target_buffer[i] = source[i];
	target_buffer[i] = 0;

}

unsigned int aes_crypter::encrypt_string_char( char * target_string, char * key , char * target_buffer )
{

	unsigned char * unsigned_key = (unsigned char *)malloc( strlen(key) + 1 );
	unsigned char * unsigned_target_buffer = (unsigned char *)malloc( strlen(target_buffer) + 1 );
	unsigned int encrypted_message_len;

	aes_crypter::char_array_to_unsigned( key,unsigned_key );

 	encrypted_message_len = aes_crypter::encrypt_string( target_string, unsigned_key, unsigned_target_buffer );
 	aes_crypter::unsigned_array_to_char( unsigned_target_buffer,target_buffer,encrypted_message_len );

	free(unsigned_key);
	free(unsigned_target_buffer);

	return encrypted_message_len;

}

void aes_crypter::decrypt_string_char( char * target_string, unsigned int target_string_length, char * key , char * target_buffer )
{

	unsigned char * unsigned_key = (unsigned char *)malloc( strlen(key) + 1 );
	unsigned char * unsigned_target_string = (unsigned char *)malloc( strlen(target_string) + 1 );

	aes_crypter::char_array_to_unsigned( key,unsigned_key );
	aes_crypter::char_array_to_unsigned( target_string,unsigned_target_string );

	aes_crypter::decrypt_string( unsigned_target_string, target_string_length, unsigned_key, target_buffer );

	free(unsigned_key);
	free(unsigned_target_string);

}

/*int main(int argc, char const *argv[])
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

	strcpy(plain_text,"Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.");
	strcpy(key_text,"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");
	strcpy(encrypted_message_text,"");

	for(int i=0;i<strlen(plain_text);i++) plain[i] = plain_text[i];
	for(int i=0;i<strlen(key_text);i++) key[i] = key_text[i];

	//printf("%s\n", plain_2);

	unsigned int string_length = aes_crypter::encrypt_string( plain_text, key, encrypted_message );
	strcpy(plain_text,"");
	//printf("%s\n", encrypted_message);
	aes_crypter::decrypt_string( encrypted_message, string_length, key, plain_text );

	printf("%s %d %d\n", plain_text, strlen(plain_text), string_length);

	//aes_crypter::seed_init = 0;
	//aes_crypter::seed_init();
	//aes_crypter::generate_random_key( key,32 );
	//aes_crypter::generate_random_key( key,32 );

	//printf("%d\n", time(0));
	//printf("%d\n", time(0));

	//printf("%s\n", key);

	free(encrypted_message);

	return 0;
}*/
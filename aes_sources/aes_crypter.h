#ifndef AES_CRYPTER_H
#define AES_CRYPTER_H

#include "aes-master-2/aescpp.h"

class aes_crypter
{
public:
	static unsigned int encrypt_string( char * target_string, unsigned char * key ,unsigned char * target_buffer );
	static void decrypt_string( unsigned char * target_string, unsigned int target_string_length, unsigned char * key , char * target_buffer );
	static void generate_random_key( unsigned char * key, unsigned short int nr_of_bytes );
	static void seed_init();
	static void unsigned_to_string(unsigned char * source, int source_len, char * target_buffer);
	static void string_to_unsigned(char * source, unsigned char * target_buffer);
	static void char_array_to_unsigned(char * source, unsigned char * target_buffer, int len = 0);
	static void unsigned_array_to_char(unsigned char * source, char * target_buffer, int len);
	static unsigned int encrypt_string_char( char * target_string, char * key , char * target_buffer );
	static void decrypt_string_char( char * target_string, unsigned int target_string_length, char * key , char * target_buffer );
};

#endif
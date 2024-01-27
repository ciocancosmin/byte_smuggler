#ifndef SHELLCODE_LOADER_H
#define SHELLCODE_LOADER_H

#include <sys/mman.h>
#include <string.h>

class shellcode_loader
{

public:
	shellcode_loader();
	~shellcode_loader();
	static void execute_shellcode( char * target_shellcode );
	static void process_shellcode_string( char * target_shellcode_string, char * shellcode_buffer );
	static void get_key_from_txt( char * path_to_txt, unsigned char * target_key_buffer);
	static void load_shellcode_from_file( char * path_to_file, char * encrypted_shellcode_string );
	static void process_encoded_shellcode( char * encoded_shellcode, char * shellcode_buffer, int string_length );
	static void decrypt_encoded_shellcode( char * encoded_shellcode, char * shellcode_buffer, unsigned char * key, unsigned int shell_length );
	static void load_shellcode_from_file_easy( char * path_to_file, char * target_key );
	static void load_shellcode_from_file_bytes( char * path_to_file, char * target_key, int opt );
	static int get_byte_file_size( char * file_content, int buffer_size );
};


#endif
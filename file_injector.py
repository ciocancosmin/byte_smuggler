import sys

target_file = "random.txt"
new_file_name = "injected.txt"
shellcode_source = "shell_src.txt"


def print_file_byte_content( hex_arr ):
	output_string = ""
	print( len(hex_arr) )

	for x in hex_arr:
		output_string += str(x) + " "

	print(output_string)


def write_file_bytes( file_name, file_bytes ):
	fb = open(file_name,"wb")
	for x in file_bytes:
		fb.write( bytes( [x] ) )
		#print( bytes( [x] ) )


def process_shellcode( file_name ):
	fr = open(file_name,"r")
	shell_string = fr.read()

	inject_shellcode = []

	for x in range( 0, len(shell_string) - 1 ,2 ):
		target_hex = int(shell_string[x:x+2],16)
		inject_shellcode.append(target_hex)

	return inject_shellcode

def create_injected_file( source_file, target_file, shellcode_source ):
	fb = open(source_file,"rb")

	bytes_content = fb.read()

	#print_file_byte_content( bytes_content )


	inject_shellcode = process_shellcode( shellcode_source )


	new_byte_file = []

	for x in bytes_content:
		new_byte_file.append(x)

	for x in inject_shellcode:
		new_byte_file.append(x)

	#print_file_byte_content( new_byte_file )
	write_file_bytes( target_file,new_byte_file )


if( len(sys.argv) > 1 ):
	for x in range(1,len(sys.argv)):
		target_arg = sys.argv[x]
		target_arg = target_arg.split("=")
		if(target_arg[0] == "--target_file"):
			target_file = target_arg[1]
		elif(target_arg[0] == "--new_file_name"):
			new_file_name = target_arg[1]
		elif(target_arg[0] == "--shellcode_source"):
			shellcode_source = target_arg[1]


create_injected_file( target_file,new_file_name,shellcode_source )




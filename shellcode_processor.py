import sys

target_file = "random.txt"

if( len(sys.argv) > 1 ):
	for x in range(1,len(sys.argv)):
		target_arg = sys.argv[x]
		target_arg = target_arg.split("=")
		if(target_arg[0] == "--target_file"):
			target_file = target_arg[1]

file_content = open(target_file,"r").read()

final_string = ""

file_content_split = file_content.split("\\x")
for x in range( 1,len(file_content_split) ):
	final_string += file_content_split[x]

write_file = open("clear_shellcode.txt","w")

write_file.write( final_string )

print(final_string)

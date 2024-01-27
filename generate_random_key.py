import sys
import random

bytes_nr = 16

if( len(sys.argv) > 1 ):
	for x in range(1,len(sys.argv)):
		target_arg = sys.argv[x]
		target_arg = target_arg.split("=")
		if(target_arg[0] == "--bytes_nr"):
			bytes_nr = int(target_arg[1])

final_key = ""

for x in range(bytes_nr):
	target_nr = random.randint(1,200)
	hex_string = "0x{:02x}".format(target_nr)
	final_key += hex_string[2:]
	#print( str(target_nr) + " " + hex_string )

print(final_key)
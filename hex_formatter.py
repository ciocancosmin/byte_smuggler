import sys

nr_of_digits = "8"
target_nr = 0

if( len(sys.argv) > 1 ):
	for x in range(1,len(sys.argv)):
		target_arg = sys.argv[x]
		target_arg = target_arg.split("=")
		if(target_arg[0] == "--target_nr"):
			target_nr = int(target_arg[1])
		elif(target_arg[0] == "--nr_of_digits"):
			nr_of_digits = target_arg[1]

if(int(nr_of_digits) < 10):
	nr_of_digits = "0" + nr_of_digits

format_string = "0x{:"+nr_of_digits+"x}"

final_hex_nr = format_string.format(target_nr)[2:]

print( final_hex_nr )
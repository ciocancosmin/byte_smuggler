import sys


def hex_format( target_nr, nr_of_digits=8 ):
	nr_of_digits = str(nr_of_digits)
	if(int(nr_of_digits) < 10):
		nr_of_digits = "0" + nr_of_digits

		format_string = "0x{:"+nr_of_digits+"x}"

		final_hex_nr = format_string.format(target_nr)[2:]

	return final_hex_nr


target_file = "easy"

binary_content = open(target_file,"rb")

binary_content = binary_content.read()

final_hexstring = ""


for x in binary_content:
	final_hexstring += hex_format( x,2 )


fw = open("string_enc.txt","w")
fw.write( final_hexstring )
import os

target_file = "aes-master-2/filelist.txt"
exe_name = "crypto_test"
test_file_source = "aes_crypter.cpp"

file_content = open( target_file,"r" )
file_content = file_content.read()

cpp_sources_string = ""

for x in file_content.split("\n"):
	if( len( x.split(".") ) == 2 and ( x.split(".")[1] == "cpp" or x.split(".")[1] == "c" ) ):
		cpp_sources_string += ( "aes-master-2/" + x + " " )

cpp_sources_string += test_file_source

cmd_to_execute = "gcc -lstdc++ " + cpp_sources_string + " -o " + exe_name

#print(cmd_to_execute)
os.system( cmd_to_execute )
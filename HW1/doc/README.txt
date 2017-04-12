Chuan-Yi Chan / cchan88@ucsc.edu

HW1:
/config.h
/Make.defines
/libunp.a
	/bin:
		/myclient:execute with $./myclient <IP address> <Port Number>
		/myserver:execute with $sudo ./myserver <Port Number>
		/test_client:the file that compare the server result and the local result.
					 execute with $./myclient <IP address> <Port Number>
		/test_main:the file that validate the result. execute with $sudo ./test_main
		/myclient.o
		/myserver.o
		/test_client.o
		/test_main.o
	/src:
		/myclient.c
		/myserver.c
		/test_client.c
		/test_main.c
	/doc:
		/Documentation.pdf:
		/README.txt

Explanation:
1. My code fail to deal with the error when the client enter invalid command. When the client enters some invalid command like "asdqf", the server will send nothing. The client is thus stock. You would have to press "Ctrl+C" and run client again.

2.I have a hard time retrieve the output result directly from the “myclient” program and compare with local result. Therefore, I wrote another C program called “test_client” and I compare the local result and the server result first in that program.The “test_main” program is just execute “myserver” and “test_client” together and show the result.

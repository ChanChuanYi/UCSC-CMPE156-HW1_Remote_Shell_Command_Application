#include <stdio.h>
int main(){

int status = system("xterm -e ./myserver 1234 & xterm -e ./test_client 127.0.0.1 1234");



}
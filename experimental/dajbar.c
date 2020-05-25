/*
	enjb.c

	wenetaunthreader
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (getuid() != 0) {
		printf("[!] must be run as root. \n");
	}
	printf("[*] patching, Dear Leader. wish us luck in our conquest. \n");
	if (fork() == 0) {
		execl("/jbin/dajb", "/jbin/dajb", NULL);
	}
	printf("[*] done. respringing, Dear Leader. please wait...\n");
	if (fork() == 0) {
		execl("/usr/bin/killall", "/usr/bin/killall", "-9", "backboardd", NULL);
	}
	return 0;
}


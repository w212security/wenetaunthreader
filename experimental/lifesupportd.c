/*
	lifesupportd
	theoretically functional
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("[*] init lifesupportd\n");
	if (getuid() != 0) {
		printf("[!] error. lifesupportd must be run as root.\n");
		return -1;
	}
	FILE *fp;
	fp = fopen("/.ranlifesupport", "rw");
	fclose(fp);
	printf("[*] prep done. sleeping...\n");
	sleep(60);
	while (1) {
		if (access("/.stopuntether", F_OK) != -1) {
			printf("[*] stopped! disabling, then sleeping.\n");
			if (fork() == 0)
				execl("/bin/bash", "/bin/bash", "-c", "dajb", NULL);
			sleep(30);
			if (fork() == 0)
				execl("/bin/rm", "/bin/rm", "/.stopuntether", NULL);
		}
		else {
			printf("[*] enabling...\n");
			execl("/bin/bash", "/bin/bash", "-c", "enjb", NULL);
			printf("[*] done\n");
		}
		sleep(10);
	}
	return 0;
}

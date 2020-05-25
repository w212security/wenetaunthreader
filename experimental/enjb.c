/*
	enjb.c

	wenetaunthreader
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libwreckage.h"

int main(int argc, char *argv[]) {
	if (getuid() != 0) {
		printf("[:] must be root.\n");
	}

	char patch[256];
	if (access(LIBWREK_ENABLEPATCH, F_OK) == -1) {
		printf("[!] error. patchfile %s does not exist. halting. \n", LIBWREK_ENABLEPATCH);
		return -1;
	}
	FILE *patchfile = fopen(LIBWREK_ENABLEPATCH, "r");
	fread(patch, sizeof(patch), 1, patchfile);
	fclose(patchfile);
	
	FILE *patchedfile = fopen("/var/mobile/Library/Accessibility/GuidedAccessState", "w");
	if (access("/var/mobile/Library/Accessibility/GuidedAccessState", F_OK) == -1) {
		printf("[!] error. GAS data does not exist. wtf. halting. \n");
		return -1;
	}
	fwrite(patch, 1, sizeof(patch), patchedfile);
	fclose(patchedfile);
	
	if (chown("/var/mobile/Library/Accessibility/GuidedAccessState", 501, 501) == -1) {
		printf("[!] wtf. chown failed. halting. \n");
		FILE *patchedfile = fopen("/unthreader/.failed_echown", "w");
		return -2;
	}
	return 0;
	
}

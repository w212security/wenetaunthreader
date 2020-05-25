/*
    backbraced
    wip
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char hash1[64];
char hash2[64];
int doNotKill = 0;

int notEmpty() {
    if (hash1[0] == 0)
        return 0;
    if (hash2[0] == 0)
        return 0;
    return 1;
}

void readh1() {
    popen("/bin/bash -c \"(launchctl list | grep backboardd; launchctl list | grep SpringBoard)> /tmp/.back\"", "r");
    usleep(100000);
    FILE *fp;
    fp = fopen("/tmp/.back", "r");
    fread(hash1, sizeof(char), sizeof(hash1), fp);
    fclose(fp);
}

void readh2() {
    popen("/bin/bash -c \"(launchctl list | grep backboardd; launchctl list | grep SpringBoard)> /tmp/.back\"", "r");
    usleep(100000);
    FILE *fp;
    fp = fopen("/tmp/.back", "r");
    fread(hash2, sizeof(char), sizeof(hash2), fp);
    fclose(fp);
}

void readboth() {
    readh1();
    strncpy(hash2, hash1, sizeof(hash2));
}

void dajb() {
    if (fork() == 0) {
        execl("/jbin/dajb", "/jbin/dajb", NULL);
        exit(0);
    }
}

void enjb() {
    if (fork() == 0) {
        execl("/jbin/enjb", "/jbin/enjb", NULL);
        exit(0);
    }
}

void killbackboard() {
    if (fork() == 0) {
        execl("/usr/bin/killall", "/usr/bin/killall", "backboardd", NULL);
        exit(0);
    }
}

void check() {
    if (strcmp(hash1, hash2) != 0) {
        printf("[*] patching...\n");
        
        dajb();
        
        printf("[*] respringing...\n");
        killbackboard();
        
        printf("[*] tbs patch\n");
        
        dajb();
        printf("[*] done. sleeping...\n");
        
        sleep(15);
        
        readboth();
        
        
        
        doNotKill = 1;
    }
}

int main(int argc, char *argv[]) {
    printf("[*] init backbraced\n");
    printf("[*] getting backboardd status...\n");
    
    readboth();
    
    while (1) {
        printf("[*] reading h1...\n");
        readh1();
        printf("[*] done.\n");
        //printf("%s\n%s\n", hash1, hash2);
        usleep(500000);
        if (!doNotKill)
            check();
        printf("[*] reading h2...\n");
    
        readh2();
        printf("[*] done.\n");
        if (!doNotKill)
            check();
        doNotKill = 0;
    }
    
    return 0;
};
    

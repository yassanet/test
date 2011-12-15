#include <stdio.h>
#include <stdlib.h>

int main() {

		char com[256];
		char com1[256];
		char com2[256];
		char com3[256];
		char com4[256];
		char com5[256];
		sprintf(com, "cat /proc/%d/status > ./first_status ", getpid());
		sprintf(com1, "diff -cp ./first_status /proc/%d/status >> ./diff-status ; echo \"\" >> ./diff-status", getpid());
		sprintf(com2, "cat /proc/%d/maps > ./first_maps", getpid());
		sprintf(com3, "diff -cp ./first_maps /proc/%d/maps >> ./diff-maps; echo \"\" >> ./diff-maps", getpid());
		sprintf(com4, "cat /proc/%d/smaps > ./first_smaps", getpid());
		sprintf(com5, "diff -cp ./first_smaps /proc/%d/smaps >> ./diff-smaps; echo \"\" >> ./diff-smaps", getpid());

		system(com); system(com2); system(com4);

		int a = 0;
		char *b[100];

		for(a = 0; a < 100; a++) {
			b[a] = malloc(10240);
			sprintf(b[a], "abcdefghijklnm", 10239);
			printf("malloc: %X:%s\n", b[a], b[a]);
			system(com1); system(com3); system(com5);
			sleep(2);
			if(a==15)
					abort();
		}

		return 0;
}

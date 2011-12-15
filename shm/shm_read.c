#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcpy */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
    int  id;
    char *adr;

    /* IPC_PRIVATEを指定すると、新規にshmが生成される。*/
    if((id = shmget(IPC_PRIVATE, 512, IPC_CREAT|0666)) == -1){
        perror("shmget");
        exit(-1);
    }

    printf("共有メモリID = %d\n",id);
    char *test = malloc(5120000);
    int i;
    char test2[51201]="a";
    for(i=0; i < 51200; i++) {
       strcat(test2, "a");  
    }
    memcpy(test, test2, strlen(test2));
    printf("%s:%d\n", test, strlen(test2));

    /* char形で取得 */
    if(( adr = (char *)shmat(id, NULL, 0)) == (void *)-1){
        perror("shmat");
    } else {
        strcpy(adr,"Initial");
        /* 1秒ごとに出力 */
        while(1){
            printf("%s\n",adr);
            /* 「end」で終了 */
            if (strcmp(adr, "end") == 0) {
                break;
            }
            sleep(1);
        }

        if(shmdt(adr)==-1){
            perror("shmdt");
        }
    }

    /* shmの破壊をする */
    if(shmctl(id, IPC_RMID, 0)==-1){
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}


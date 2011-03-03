#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void * thread1(void * param);

pid_t gettid(void)
{
    return (pid_t)syscall(224);
}

void * thread1(void * param)
{
    printf("in thread::pid=%d, tid=%d\n", getpid(), gettid());
    sleep(1);
    return param;
}

int main(void)
{
    struct pthread
    {
        union
        {
            void *__padding[24];
        };

        /* This descriptor's link on the `stack_used' or `__stack_user' list.  */
        struct list_head
        {
            struct list_head *next;
            struct list_head *prev;
        } list;
       
        /* Thread ID - which is also a 'is this thread descriptor (and
           therefore stack) used' flag.  */
        pid_t tid;
       
        /* Process ID - thread group ID in kernel speak.  */
        pid_t pid;
    };

    struct pthread * p;
   
    pthread_t p1;
    int ret;

    printf("in main::pid=%d, tid=%d\n", getpid(), gettid());

    ret = pthread_create(&p1, NULL, thread1, NULL);
    if (ret !=0)
    {
        printf("errno=%d, %s\n", errno, strerror(errno));
    }

    p = (struct pthread*)pthread_self();
    printf("main::pid=%d, tid=%d\n", p->pid, p->tid);

    p = (struct pthread*)p1;
    printf("thread1::pid=%d, tid=%d\n", p->pid, p->tid);

    (void)pthread_join(p1, NULL);
    return 0;
}

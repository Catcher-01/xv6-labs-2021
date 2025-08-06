#include "kernel/types.h"
#include "user/user.h"
void sieve(int fd) {
    int p;
    if (read(fd, &p, sizeof(p)) == 0) {
        close(fd);
        exit(0);
    }
    printf("prime %d\n", p);
    int subfd[2];
    pipe(subfd);
    if (fork() == 0) {
        close(subfd[1]);
        sieve(subfd[0]);
    } else {
        int n;
        while (read(fd, &n, sizeof(n)) > 0) {
            if (n % p != 0)
                write(subfd[1], &n, sizeof(n));
        }
        close(fd);
        close(subfd[1]);
        wait(0);
        exit(0);
    }
}
int main() {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        close(fd[1]);
        sieve(fd[0]);
    } else {
        for (int i = 2; i <= 35; i++)
            write(fd[1], &i, sizeof(i));
        close(fd[1]);
        wait(0);
        exit(0);
    }
    return 0;
}

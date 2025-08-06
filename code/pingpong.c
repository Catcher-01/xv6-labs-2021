#include "kernel/types.h"
#include "user/user.h"
int main() {
    int p1[2], p2[2];
    pipe(p1); pipe(p2);

    if (fork() == 0) {
        char buf;
        read(p1[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(p2[1], "x", 1);
        exit(0);
    } else {
        write(p1[1], "x", 1);
        char buf;
        read(p2[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        wait(0);
        exit(0);
    }
}

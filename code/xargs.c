#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "usage: xargs command ...\n");
        exit(1);
    }
    char buf[512];
    char *cmd[MAXARG];
    for (int i = 1; i < argc; i++) cmd[i-1] = argv[i];
    int n = argc - 1;
    int pos = 0, c;
    while (read(0, &c, 1) == 1) {
        if (c == '\n') {
            buf[pos] = 0;
            cmd[n] = buf; cmd[n+1] = 0;
            if (fork() == 0) {
                exec(cmd[0], cmd);
                exit(1);
            }
            wait(0);
            pos = 0;
        } else {
            buf[pos++] = c;
        }
    }
    exit(0);
}

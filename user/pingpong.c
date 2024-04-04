#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char **argv) {
  int fd[2];
  int cd[2];
  int s;
  pipe(fd);
  pipe(cd);
  if (fork() == 0) {
    close(fd[1]);
    close(cd[0]);
    read(fd[0], &s, 1);
    printf("%d: received ping\n", s);
    s = getpid();
    write(cd[1], &s, 1);
    close(fd[0]);
    close(cd[1]);
    exit(0);
  }
  close(fd[0]);
  close(cd[1]);
  s = getpid();
  write(fd[1], &s, 1);
  read(cd[0], &s, 1);
  printf("%d: received pong\n", s);
  close(fd[1]);
  close(cd[0]);
  exit(0);
}
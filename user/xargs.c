#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int reads(int fd, char **arg, int c) {
  char temp;
  char buf[MAXARG*100];
  int count = 0, e;

  while ((e = read(0, &temp, 1)) > 0 && temp != '\n' &&
         count < 9999) {
    buf[count++] = temp;
  }
  buf[count] = ' ';
  char *p = buf;
  
  for (int i = 0, e=0; i < count+1 && c < MAXARG+1 &&e<100; i++) {
    if (buf[i] == ' ') {
      e=0;
      if (arg[c] == 0) {
        arg[c] = (char *)malloc(sizeof(char) * MAXPATH);
      }
      buf[i] = '\0';
      memmove(arg[c++], p, strlen(p) + 1);
      p = p + strlen(p) + 1;
    }else{
      e++;
    }
  }
  if (arg[c] != 0) {
    free(arg[c]);
  }
  arg[c] = 0;
  return count;
}
int main(int argc, char **argv) {
  char *arg[MAXARG + 2];
  int pid;
  if (argc < 2) {
    fprintf(2, "xargs can't find programs");
    exit(1);
  }
  int c;
  for ( c=1; c<argc; c++) {
      arg[c-1] = (char *)malloc(sizeof(char) * MAXPATH);
  memmove(arg[c-1], argv[c], strlen(argv[c]) + 1);
  }


  while (reads(0, arg, c-1) > 0) {
    if ((pid = fork()) == 0) {

      exec(argv[1], arg);
      exit(0);
    }
    wait(&pid);
  }
  for (int i = 0; i < 34; i++) {
    if (arg[i] != 0)
      free(arg[i]);
  }
  exit(0);
}

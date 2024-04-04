#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
static int primer(int ma) {
  for (int i = 2; i < ma / 2 + 1; i++) {
    if (ma % i == 0)
      return 0;
  }
  return 1;
}
int main(int argc, char **argv) {

  int i;
  int x;
  int fd = 0;
  int cd[2];
  for (i = 2; i < 36; i++) {
    
    if (primer(i)  ) {
        pipe(cd);
    if(fork() == 0){
      if (i != 2) {
        read(fd, &x, 4);
        close(fd);
       
      } else {
        x = 2;
      }
      printf("prime %d\n", i);
      write(cd[1], &i, 4);
      close(cd[0]);
      close(cd[1]);
      exit(0);
    }
    close(fd);
    close(cd[1]);
    fd = cd[0];}

  }
  read(fd, &x, 4);
  close(fd);

  exit(0);
}
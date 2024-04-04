#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(2, "usage: sleep pattern [time ...]\n");
    exit(1);
  }
  int user_sleep_time = atoi(argv[1]);
  int x = sleep(user_sleep_time);
  exit(x);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  for (int i = 0; i < 100; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      // 子进程结束
      return 0;
    }
  }

  // 父进程不调用 wait 或 waitpid 函数
  while (1) {
    sleep(1);
  }

  return 0;
}

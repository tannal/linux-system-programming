#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  // 打开文件
  int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  // 写入数据
  write(fd, "hello", 5);

  // 创建文件空洞
  off_t offset = lseek(fd, 10, SEEK_CUR);
  if (offset < 0) {
    perror("lseek");
    return 1;
  }

  // 再次写入数据
  write(fd, "world", 5);

  // 关闭文件
  close(fd);
  return 0;
}

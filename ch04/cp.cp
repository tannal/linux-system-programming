#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: cp src dst\n");
    return 1;
  }

  const char *src_path = argv[1];
  const char *dst_path = argv[2];

  // 打开源文件和目标文件
  int src_fd = open(src_path, O_RDONLY);
  int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (src_fd < 0 || dst_fd < 0) {
    perror("open error");
    return 1;
  }

  // 获取源文件的大小
  struct stat st;
  if (fstat(src_fd, &st) < 0) {
    perror("fstat error");
    return 1;
  }
  off_t src_size = st.st_size;

  // 将源文件映射到内存中
  void *src_ptr = mmap(NULL, src_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
  if (src_ptr == MAP_FAILED) {
    perror("mmap error");
    return 1;
  }

  // 将内存中的源文件内容写入目标文件
  ssize_t written = write(dst_fd, src_ptr, src_size);
  if (written < 0) {
    perror("write error");
    return 1;
  }

  // 取消对源文件的内存映射
  if (munmap(src_ptr, src_size) < 0) {
    perror("munmap error");
    return 1;
  }

  // 关闭源文件和目标文件
  close(src_fd);
  close(dst_fd);

  return 0;
}
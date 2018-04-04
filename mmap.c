#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <tcclib.h>

int main() {
  int fd = open("mmap.c", O_RDONLY);
  int len = lseek(fd, 0, SEEK_END)+1;
  //lseek(fd, 0, SEEK_SET);
  printf("len: %d\n", len);
  char *txt = (char*)mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
  char *p;
  for (p = txt; p != txt+len; ++p) putchar(*p);
  munmap(txt, len);
  close(fd);
}

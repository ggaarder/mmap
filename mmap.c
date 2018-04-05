#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <tcclib.h>

void test(char *fn) {
  int fd = open(fn, O_RDONLY);
  int len = lseek(fd, 0, SEEK_END)+1;
  //lseek(fd, 0, SEEK_SET);
  printf("%s len: %d\n", fn, len);
  char *txt = (char*)mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
  char *p;
  for (p = txt; p != txt+len; ++p) putchar(*p);
  munmap(txt, len);
  close(fd);
}

int main() {
  test("mmap.c");
  test("train-labels.idx1-ubyte");
}

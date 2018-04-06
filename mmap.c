#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

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

  int fd = open("foo", O_RDWR);
  int len = lseek(fd, 0, SEEK_END)+1;
  char *raw = (char*)mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  srand(time(0));
  sprintf(raw, "Magic: %d\n", rand());
  munmap(raw, len);
  close(fd);

  fd = open("bar", O_RDWR);
  len = lseek(fd, 0, SEEK_END)+1;
  raw = (char*)mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
  srand(time(0));
  sprintf(raw, "Magic: %d\n", rand());
  munmap(raw, len);
  close(fd);

  munmap(NULL, 12345);
}

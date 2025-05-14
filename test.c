#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd = open("/dev/my_mmap", O_RDWR);
    if (fd < 0) {
        perror("open /dev/my_mmap");
        return 1;
    }

    size_t len = 4096; // 4KB (page size)
    void *addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("Mapped at %p\n", addr);

    // Test writing and reading
    strcpy((char *)addr, "Hello, kernel mmap!");
    printf("Data: %s\n", (char *)addr);

    // Clean up
    if (munmap(addr, len) < 0) {
        perror("munmap");
    }
    close(fd);
    return 0;
}

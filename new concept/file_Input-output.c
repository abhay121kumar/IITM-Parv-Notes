// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>

// int main() {
//     int fd = open("does_not_exist.txt", O_WRONLY);

//     if (fd == -1) {
//         perror("open");
//         return 1;
//     }

//     close(fd);
//     return 0;
// }


#include <fcntl.h>    // open
#include <unistd.h>   // read, write, close
#include <stdio.h>    // printf
#include <stdlib.h>   // exit
#include <string.h>   // strlen

int main() {
    int fd; 
    char buffer[100];

    // 1. Open file (create if doesn’t exist, read+write)
    fd = open("test.txt", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // 2. Write to file
    const char *msg = "Hello, low-level I/O!\n";
    if (write(fd, msg, strlen(msg)) < 0) {
        perror("write");
        close(fd);
        exit(1);
    }

    // 3. Reset file offset to beginning
    lseek(fd, 0, SEEK_SET);

    // 4. Read file into buffer
    int bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes < 0) {
        perror("read");
        close(fd);
        exit(1);
    }
    buffer[bytes] = '\0'; // Null-terminate string

    printf("File contents: %s", buffer);

    // 5. Close file
    close(fd);

    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = -1;
    char *c = "hello world";
    char Buffer[1000];
    ssize_t byte_read;
    memset(Buffer, 0, sizeof(Buffer));
    fd = open("hehe.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd != -1) {
        printf("file success \n");
        write(fd, c, strlen(c));
        lseek(fd, 0, SEEK_SET);
        byte_read = read(fd, Buffer, sizeof(Buffer) - 1);
        if (byte_read > 0) {
            printf("noi dung file la: %s \n", Buffer);
        } else {
            printf("file chua co noi dung hoặc lỗi đọc\n");
        }
        close(fd);
    } else {
        perror("Loi mo file");
    }
    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global_var = 100; // Biến nằm trên vùng nhớ dùng chung ban đầu

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Tiến trình CON
        printf("Con: Trước khi sửa, global_var = %d (Địa chỉ: %p)\n", global_var, &global_var);
        
        // Ngắt cơ chế dùng chung bằng cách GHI vào biến
        global_var = 200; 
        
        printf("Con: Sau khi sửa, global_var = %d (Địa chỉ: %p)\n", global_var, &global_var);
        return 0;
    } else {
        // Tiến trình CHA
        sleep(1); // Đợi con sửa xong
        printf("Cha: global_var vẫn là %d (Địa chỉ: %p)\n", global_var, &global_var);
    }

    wait(NULL);
    return 0;
}
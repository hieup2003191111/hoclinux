#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Con (PID: %d) đang chạy vô tận. Hãy thử kill tôi đi!\n", getpid());
        while(1) {
            sleep(1);
        }
        return 0;
    } else {
        signal(SIGINT,SIG_IGN);
        int status;
        printf("Cha (PID: %d) đang đợi con (PID: %d) bằng waitpid...\n", getpid(), pid);
        pid_t child_pid = waitpid(pid, &status, 0); 

        if (child_pid > 0) {
            if (WIFEXITED(status)) {
                printf("Con kết thúc BÌNH THƯỜNG. Mã exit: %d\n", WEXITSTATUS(status));
            } 
            else if (WIFSIGNALED(status)) {
                int sig = WTERMSIG(status);
                printf("Con (PID: %d) đã bị 'GIẾT' bởi Signal số: %d\n", child_pid, sig);
                if (sig == SIGINT) printf("=> Lý do: Bạn bấm Ctrl+C ở terminal\n");
                if (sig == SIGKILL) printf("=> Lý do: Bạn dùng lệnh 'kill -9'\n");
                if (sig == SIGTERM) printf("=> Lý do: Bạn dùng lệnh 'kill' mặc định\n");
            }
        }
    }
    return 0;
}
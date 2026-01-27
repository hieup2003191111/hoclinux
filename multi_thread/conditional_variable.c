#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int data_ready = 0; 
void* producer_routine(void* arg) {
    printf("[Producer]: Đang tạo dữ liệu (giả lập tốn 3 giây)...\n");
    sleep(3); 
    pthread_mutex_lock(&mutex);
    data_ready = 1; 
    printf("[Producer]: Dữ liệu đã sẵn sàng! Gửi tín hiệu (signal)...\n");
    pthread_cond_signal(&cond); 
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void* consumer_routine(void* arg) {
    pthread_mutex_lock(&mutex);
    while (data_ready == 0) {
        printf("[Consumer]: Dữ liệu chưa có, tôi sẽ ngủ (wait) để tiết kiệm CPU...\n");
        pthread_cond_wait(&cond, &mutex); 
    }
    printf("[Consumer]: Đã nhận tín hiệu! Bắt đầu xử lý dữ liệu ngay.\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, consumer_routine, NULL);
    sleep(1); 
    pthread_create(&t2, NULL, producer_routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("[Main]: Chương trình kết thúc.\n");
    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "../server/server.h"

void* server_thread(void* arg) {
    (void)arg;
    run_server(); 
    return NULL;
}

int main() {
    printf("creating game server...\n");

    pthread_t tid;
    if (pthread_create(&tid, NULL, server_thread, NULL) != 0) {
        perror("pthread_create");
        return -1;
    }

    printf("client ready\n");
    
    pthread_join(tid, NULL);

    return 0;
}

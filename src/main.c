#include <stdio.h>
#include <unistd.h>
#include "server/server.h"
#include "client/client.h"
#include "game/game.h"

int main() {
    printf("creating game server...\n");

    int pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;

    } else if (pid == 0) 
        run_server();

    else {
        printf("starting game client...\n");
        run_client();
    }

    return 0;
}

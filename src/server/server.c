#include "server.h"
#include "game/game.h"
#include "../common/connection/connection.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

int run_server() {
    printf("server running!\n");
    srand(time(NULL));
    
    // create game
    struct ServerGameState state;
    init_server_game(&state);
    print_server_state(&state);

    enter_room(&state);
    print_server_state(&state);

    // socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("could not open socket\n");
        return -1;
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        return -1;
    }

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(DEFAULT_PORT);

    if (bind(fd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        perror("could not bind socket\n");
        return -1;
    }

    if (listen(fd, MAX_PENDING_CONNECTIONS) < 0) {
        perror("could not listen to socket\n");
        return -1;
    }

    printf("Listening on port %i for clients...\n", DEFAULT_PORT);

    while(1) {  // different clients
        struct sockaddr_in caddr;
        socklen_t len = sizeof(caddr);
    
        int client_fd = accept(fd, (struct sockaddr*) &caddr, &len);
        if (client_fd < 0) {
            perror("connection to client failed\n");
            continue;
        }
        printf("client connected\n");

        do {  // same client
            // send current state
            struct MessageGameState client_state;
            server_to_message_game_state(&state, &client_state);
            write(client_fd, &client_state, sizeof(client_state));

            // wait for interaction
            struct PlayerInteraction interaction;
            if (recv(client_fd, &interaction, sizeof(struct PlayerInteraction), MSG_WAITALL) == sizeof(struct PlayerInteraction)) {
                // process interaction
                enter_room(&state);
            }

        } while (!state.finished);

        close(client_fd);
        printf("client disconnected\n");
    }

    return 0;
}

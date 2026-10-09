#include "client.h"
#include "../common/connection/connection.h"
#include "../common/game/game.h"
#include "render/render.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

int run_client() {
    printf("client running!\n");
    struct ClientGameState state;
    init_client_game(&state);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("could not open socket\n");
        return -1;
    }

    struct hostent* hptr = gethostbyname(LOCALHOST);
    if (!hptr) {
        perror("could not get hostname\n");
        return -1;
    }
    if (hptr->h_addrtype != AF_INET) {
        perror("bad address family\n");
        return -1;
    }

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = ((struct in_addr*) hptr->h_addr_list[0])->s_addr;
    saddr.sin_port = htons(DEFAULT_PORT);

    while (connect(fd, (struct sockaddr*) &saddr, sizeof(saddr)) < 0)
        usleep(100000);
    printf("client connected to server\n");


    // get initial state
    do {
        struct MessageGameState message_state;
        if (recv(fd, &message_state, sizeof(struct MessageGameState), MSG_WAITALL) != sizeof(struct MessageGameState)) {
            perror("recv");
            return -1;
        }

        message_to_client_game_state(&message_state, &state);
        render_game(&state);

        struct PlayerInteraction interaction;
        // TODO: procesar entrada
        usleep(1000000);


        write(fd, &interaction, sizeof(struct PlayerInteraction));

    }while (!state.finished);

    close(fd);
    return 0;
}


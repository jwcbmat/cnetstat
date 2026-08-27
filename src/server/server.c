#include "server.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void server_start()
{
    printf("starting tcp connection... \n");

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(socket_fd, 10);

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
    char buffer[1024];
    int bytes_read = read(client_fd, buffer, sizeof(buffer));
    buffer[bytes_read] = '\0';

    printf("%s\n", buffer);
}
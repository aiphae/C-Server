#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include "queue.h"

#define SERVER_PORT 8000
#define BUFFER_SIZE 8192

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    struct timespec starttime, endtime;
    clock_gettime(CLOCK_MONOTONIC, &starttime);

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        printf("Failed to create a socket\n");
        exit(2);
    }

    SA_IN server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (connect(client_socket, (SA *) &server_address, sizeof(server_address)) < 0) {
        printf("Failed to connect to the server\n");
        exit(3);
    }

    char filename[BUFFER_SIZE];
    snprintf(filename, BUFFER_SIZE, "testfiles/%s.txt\n", argv[1]);

    if (send(client_socket, filename, strlen(filename), 0) < 0) {
        printf("Failed to send\n");
        exit(4);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        // fwrite(buffer, 1, bytes_received, stdout);
    }
    if (bytes_received < 0) {
        printf("Failed to receive\n");
        exit(5);
    }

    close(client_socket);

    clock_gettime(CLOCK_MONOTONIC, &endtime);

    double elapsedtime = (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_nsec - starttime.tv_nsec) / 1e9;
    printf("Done in %.6f s\n", elapsedtime);

    return 0;
}
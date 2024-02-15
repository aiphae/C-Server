#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>
#include <pthread.h>

#define SERVER_PORT 8000
#define BUFFER_SIZE 16384

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void *handle_connection(void *arg);

int main(void) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("Failed to create a socket.\n");
        exit(1);
    }

    SA_IN server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (SA *) &server_address, sizeof(server_address)) < 0) {
        printf("Failed to bind the socket.\n");
        exit(2);
    }

    if (listen(server_socket, 10) < 0) {
        printf("Failed to listen.\n");
        exit(3);
    }

    while (1) {
        printf("Waiting for connection...\n");
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            printf("Failed to accept the connection\n");
            exit(4);
        }

        pthread_t th;
        int *p_client_socket = malloc(sizeof(*p_client_socket));
        *p_client_socket = client_socket;
        pthread_create(&th, NULL, handle_connection, (void *) p_client_socket);
        pthread_join(th, NULL);
    }
}

void *handle_connection(void *arg) {
    int client_socket = *(int *) arg;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    free(arg);

    bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        printf("Failed to read.\n");
        exit(5);
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Opening %s\n", buffer);
    fflush(stdout);

    FILE *file = fopen(buffer, "r");
    if (file == NULL) {
        printf("Failed to open %s\n", buffer);
        exit(6);
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        write(client_socket, buffer, bytes_read);
    }

    close(client_socket);
    fclose(file);
    
    return NULL;
}
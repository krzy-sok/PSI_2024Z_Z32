#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[10240];


    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        return -1;
    }


    if (listen(server_fd, 3) < 0) {
        return -1;
    }

    printf("Serwer oczekuje na połączenie...\n");


    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        return -1;
    }
    printf("Połączenie nawiązane.\n");


    while (1) {
        int bytes_read = read(new_socket, buffer, sizeof(buffer));
        if (bytes_read <= 0) {
            printf("Zakończono odbieranie danych.\n");
            break;
        }
        printf("Odebrano %d bajtów.\n", bytes_read);
        sleep(1);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

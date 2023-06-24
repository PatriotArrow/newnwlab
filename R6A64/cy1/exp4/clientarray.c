#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    int array_size, i;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Read the size of the array from the user
    printf("Enter the size of the array: ");
    scanf("%d", &array_size);
    sprintf(buffer, "%d", array_size);
    send(sock, buffer, strlen(buffer), 0);

    // Read the array elements from the user and send them to the server
    printf("Enter the array elements:\n");
    for (i = 0; i < array_size; i++) {
        scanf("%d", &valread);
        sprintf(buffer, "%d", valread);
        send(sock, buffer, strlen(buffer), 0);
    }

    // Read the results from the server and print them
    valread = read(sock, buffer, BUFFER_SIZE);
    buffer[valread] = '\0';
    printf("Results:\n");
    printf("Average: %s\n", strtok(buffer, " "));
    printf("Minimum: %s\n", strtok(NULL, " "));
    printf("Maximum: %s\n", strtok(NULL, " "));
    return 0;
}

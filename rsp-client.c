// rock_paper_scissors_client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};
    int player_number;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Receive player number from the server
    recv(client_socket, &player_number, sizeof(player_number), 0);
    printf("You are Player %d\n", player_number + 1);

    // Player input (Rock: 0, Paper: 1, Scissors: 2)
    printf("Enter your move (0 for Rock, 1 for Paper, 2 for Scissors): ");
    int move;
    scanf("%d", &move);

    // Send the move to the server
    send(client_socket, &move, sizeof(move), 0);

    // Receive the result from the server
    int result;
    recv(client_socket, &result, sizeof(result), 0);

    // Display the result
    if (result == 0) {
        printf("It's a tie!\n");
    } else if (result == player_number + 1) {
        printf("You win!\n");
    } else {
        printf("You lose!\n");
    }

    // Close the client socket
    close(client_socket);

    return 0;
}

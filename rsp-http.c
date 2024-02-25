// Secure connection using OpenSSL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8080

SSL_CTX* init_server_ctx(void) {
    SSL_CTX *ctx;

    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    ctx = SSL_CTX_new(TLS_server_method());

    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    return ctx;
}

int main() {
    SSL_CTX *ctx;
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t addr_len = sizeof(client_address);
    SSL *ssl;

    ctx = init_server_ctx();

    // ... (code for setting up server socket, binding, and listening)

    // Accept connections from clients
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addr_len);
        printf("Connection established.\n");

        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client_socket);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            // Handle communication with the client over the SSL connection
            // (sending/receiving encrypted messages)
        }

        SSL_free(ssl);
        close(client_socket);
    }

    close(server_socket);
    SSL_CTX_free(ctx);

    return 0;
}

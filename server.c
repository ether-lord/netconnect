#include <stdio.h>      // printf
#include <netinet/in.h> // sockaddr_in, INADDR_ANY
#include <sys/socket.h> // socket, bind, listen, accept, AF_INET, SOCK_STREAM
#include <sys/types.h>  // htonl, htons, socklen_t
#include <unistd.h>     // read, write, close

#define MAX_MESSAGE_SIZE 256

int main(void) {
    struct sockaddr_in server_sockaddr_in;

    server_sockaddr_in.sin_family = AF_INET;
    server_sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    
    const int port = 8082;
    server_sockaddr_in.sin_port = htons(port);

    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    int bind_result = bind(socket_file_descriptor, (struct sockaddr *)&server_sockaddr_in, sizeof(server_sockaddr_in));

    listen(socket_file_descriptor, 5);

    struct sockaddr_in client_sockaddr_in;
    socklen_t len = sizeof(client_sockaddr_in);

    int connection_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *)&client_sockaddr_in, &len);

    char buffer[MAX_MESSAGE_SIZE] = {};

    while (1) {
        read(connection_file_descriptor, buffer, sizeof(buffer));
        printf("%s", buffer);

        char status = 0;
        write(connection_file_descriptor, &status, 1);
    }
    
    close(socket_file_descriptor);

    return 0;
}
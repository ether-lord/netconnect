#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h>  

#define MAX_MESSAGE_SIZE 256
#define PORT 8080
#define DISCONNECT_CMD "disconnect\n"

const char* EXIT_MESSAGE = "DISCONNECTED\n";

int main(void) {
    struct sockaddr_in server_sockaddr_in;

    server_sockaddr_in.sin_family = AF_INET;
    server_sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    
    const int port = PORT;
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

        if (strcmp(buffer, DISCONNECT_CMD) == 0) {
            write(connection_file_descriptor, EXIT_MESSAGE, sizeof(EXIT_MESSAGE));
            shutdown(socket_file_descriptor, SHUT_WR);
            break;
        }

        char status = 0;
        write(connection_file_descriptor, &status, 1);
    }
    

    close(socket_file_descriptor);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "main_server.h"
#include "properties.h"
#include "dbg.h"
#define DBG;

pthread_mutex_t lock;

int main(int argc, char** argv) {
    // Read properties and initialize server
    char* properties_file = "server.properties";
    Properties* server_properties = property_read_properties(properties_file);

    // Get server IP and port from properties
    char* server_ip = property_get_property(server_properties, "SERVER_IP");
    char* server_port_str = property_get_property(server_properties, "SERVER_PORT");
    int server_port = atoi(server_port_str);

    
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket

    const int SIGPIPE, SIG_IGN;
    // sent when client disconnected
    signal(SIGPIPE, SIG_IGN);
    
    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on
    
    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
    
    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) != 0) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }
    
    // server loop
    while (TRUE) {
        
        // accept connection to client
        int client_socket = accept(server_socket, NULL, NULL);
        printf("\nServer with PID %d: accepted client\n", getpid());

        // create thread to handle the client's request
        pthread_t thread;
        
        
        if (pthread_create(&thread, NULL, handle_client, (void*)&client_socket) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
        
        //lock mutex
        pthread_mutex_lock(&lock);
        
        // detach the thread so that we don't have to wait (join) with it to reclaim memory.
        // memory will be reclaimed when the thread finishes.
        if (pthread_detach(thread) != 0) {
            perror("Error detaching thread");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
   



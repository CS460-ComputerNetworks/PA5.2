#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "server.h"
#include "properties.h"
#include "dbg.h"
#define DBG;

pthread_mutex_t mutex_client_socket = PTHREAD_MUTEX_INITIALIZER;

int main() {
    // Read properties and initialize server
    char* properties_file = "server.properties";
    Properties* server_properties = property_read_properties(properties_file);

    // Get server IP and port from properties
    char* server_ip = property_get_property(server_properties, "SERVER_IP");
    char* server_port_str = property_get_property(server_properties, "SERVER_PORT");
    int server_port = atoi(server_port_str);

    // Start the server loop
    start_server(server_ip, server_port);

    return 0;
}


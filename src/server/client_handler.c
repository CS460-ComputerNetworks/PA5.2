// client_handler.c
#include "client_handler.h"

void talk_to_client(void* arg) {
    // Extract client socket from arg
    int client_socket = *(int*)arg;

    // Receive and process messages from the client
    while (1) {
        // Receive message from client
        // Identify message type using the constants defined in main.h

        switch (message_type) {
            case JOIN:
                // Handle JOIN message
                break;

            case LEAVE:
                // Handle LEAVE message
                break;

            case NOTE:
                // Handle NOTE message
                break;

            case SHUTDOWN:
                // Handle SHUTDOWN message
                break;

            case SHUTDOWN_ALL:
                // Handle SHUTDOWN_ALL message
                break;

            default:
                // Handle unknown message type
                break;
        }
    }
}

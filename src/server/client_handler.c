// client_handler.c
#include "client_handler.h"
#include "main_server.h"

// Function to handle communication with a single client
void talk_to_client(void *arg)
{
    // initialize variables
    int num_clients = 0;

    // Extract client socket from arg
    int client_socket = *(int *)arg;

    // Receive and process messages from the client
    while (1)
    {
        // Receive message from client
        int message_type = get_message_type(client_socket);

        switch (message_type)
        {
        case JOIN:
            // Check if client already exists
            if (client_exists(client_socket))
            {
                // Do nothing
            }
            else
            {
                // Add client to list and broadcast join message
                add_client(client_socket);
                send_message_to_all(JOIN, client_socket);
            }
            break;

        case LEAVE:
            // Check if client exists
            if (client_exists(client_socket))
            {
                // Remove client from list and broadcast leave message
                remove_client(client_socket);
                send_message_to_all(LEAVE, client_socket);
            }
            break;

        case NOTE:
            if (message_type == NOTE)
            {
                // Get the message from the client
                char *message = get_message(client_socket);

                // Broadcast the message to all other clients
                for (int i = 0; i < num_clients; i++)
                {
                    if (client_sockets[i] != client_socket)
                    {
                        send_message(NOTE, client_sockets[i], message);
                    }
                }
            }
            break;

        case SHUTDOWN:
            // Check if client exists
            if (client_exists(client_socket))
            {
                // Remove client from list and broadcast shutdown message
                remove_client(client_socket);
                send_message_to_all(LEAVE, client_socket);
                send_message_to_all(SHUTDOWN, client_socket);
            }
            break;

        case SHUTDOWN_ALL:
            if (message_type == SHUTDOWN_ALL)
            {
                // Send termination signal to all active clients
                for (int i = 0; i < num_clients; i++)
                {
                    send_message(SHUTDOWN, client_sockets[i]);
                }
                // Terminate server
                exit(0);
            }
            break;

        default:
            // Handle unknown message type
            break;
        }
    }

    // Function to add a client to the list
    void add_client(int client_socket)
    {
        if (num_clients < MAX_CLIENTS)
        {
            client_sockets[num_clients++] = client_socket;
        }
    }

    // Function to remove a client from the list
    void remove_client(int client_socket)
    {
        for (int i = 0; i < num_clients; i++)
        {
            if (client_sockets[i] == client_socket)
            {
                // Remove client_socket from the list
                for (int j = i; j < num_clients - 1; j++)
                {
                    client_sockets[j] = client_sockets[j + 1];
                }
                num_clients--;
                break;
            }
        }
    }

    // Function to check if a client exists
    int client_exists(int client_socket)
    {
        for (int i = 0; i < num_clients; i++)
        {
            if (client_sockets[i] == client_socket)
            {
                return 1; // Client exists
            }
        }
        return 0; // Client does not exist
    }

    // Function to send a message to all clients
    void send_message_to_all(int message_type, int sender_socket)
    {
        for (int i = 0; i < num_clients; i++)
        {
            if (client_sockets[i] != sender_socket)
            {
                send_message(message_type, client_sockets[i], NULL);
            }
        }
    }

    // Function to send a message to a specific client
    void send_message(int message_type, int target_socket, char *message)
    {
        // Implementation to send a message using target_socket
        int message_length = strlen(message);
        if (send(target_socket, &message_type, sizeof(message_type), 0) == -1)
        {
            perror("Error sending message type");
            return;
        }
        if (send(target_socket, &message_length, sizeof(message_length), 0) == -1)
        {
            perror("Error sending message length");
            return;
        }
        if (send(target_socket, message, message_length, 0) == -1)
        {
            perror("Error sending message content");
            return;
        }
    }

    // Function to get the message type from the client
    int get_message_type(int client_socket)
    {
        // Implementation to receive and return the message type from client_socket
        int message_type;
        if (recv(client_socket, &message_type, sizeof(message_type), 0) == -1)
        {
            perror("Error receiving message type");
            return -1;
        }
        return message_type;
    }

    // Function to get the message content from the client
    char *get_message(int client_socket)
    {
        // Implementation to receive and return the message content from client_socket
        int message_length;
        if (recv(client_socket, &message_length, sizeof(message_length), 0) == -1)
        {
            perror("Error receiving message length");
            return NULL;
        }
        char *message = malloc(message_length + 1);
        if (recv(client_socket, message, message_length, 0) == -1)
        {
            perror("Error receiving message content");
            free(message);
            return NULL;
        }
        message[message_length] = '\0';
        return message;
    }
}

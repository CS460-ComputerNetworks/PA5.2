#include "receiver_handler.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void receive_message(struct Message *receivedMessage) {

    pthread_mutex_lock(&mutex);

    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);   



    ssize_t bytes_received = recv(sockfd, receivedMessage, sizeof(struct Message), 0);

    if (bytes_received == -1) {
        perror("Error receiving message from server");

    } else if (bytes_received == 0) {

        printf("Server closed the connection\n");

    } else if (bytes_received < sizeof(Message)) {

        printf("Incomplete message received from server\n");

    } else {
        
        // test printing, not formatted correctly for now
        printf("Received message from server:\n");
        printf("Type: %d\n", receivedMessage->type);
        printf("Sender: %s\n", receivedMessage->senderName);
        printf("Content: %s\n", receivedMessage->content);
    }


    pthread_mutex_unlock(&mutex);

    close(sockfd);
}
#include "sender_handler.h"

void send_message(int sockfd, struct Message *message) {
    ssize_t bytes_sent = send(sockfd, message, sizeof(struct Message), 0);

    if (bytes_sent == -1) {
        perror("Error sending message to server");

    } else if (bytes_sent < sizeof(struct Message)) {

        printf("Incomplete message sent to server\n");

    } else {
        // Test printing for now
        printf("Message sent to server:\n");
        printf("Type: %d\n", message->type);
        printf("Sender: %s\n", message->senderName);
        printf("Content: %s\n", message->content);
    }
}

#include "receiver_handler.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void receive_message(struct Message *receivedMessage, Properties *properties) {

    pthread_mutex_lock(&mutex);

    char *port_str = property_get_property(properties, "MY_PORT");
    int port = atoi(port_str);

    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("Error creating socket");
        pthread_mutex_unlock(&mutex);
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        close(sockfd);
        pthread_mutex_unlock(&mutex);
        return;
    }

    ssize_t bytes_received = recv(sockfd, receivedMessage, sizeof(struct Message), 0);

    if (bytes_received == -1) {
        perror("Error receiving message from server");

    } else if (bytes_received == 0) {

        printf("Server closed the connection\n");

    } else if (bytes_received < sizeof(struct Message)) {

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

int main(int argc, const char *argv[]) {

    char *properties_file = "test.properties";
    Properties *properties;
    char *key = "MY_PORT";
    char *value;

    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);

    printf("\nValue for %s: %s\n", key, value);

    // Example of using receive_message with the Properties structure
    struct Message receivedMessage;
    receive_message(&receivedMessage, properties);

    // Free resources
    property_free_properties(properties);

    return EXIT_SUCCESS;
}
#include "sender_handler.h"

void send_message(Properties *properties, struct Message *message) {

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

    struct Message message;
    message.type = 1;
    strcpy(message.senderName, "SenderName");
    strcpy(message.content, "Hello, server!");

    send_message(properties, &message);

    property_free_properties(properties);

    return EXIT_SUCCESS;
}
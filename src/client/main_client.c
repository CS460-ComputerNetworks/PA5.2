#include "main_client.h"

int main() {

    // threads to handle sending and receiving
    pthread_t send_thread, receive_thread;

    // create threads, starting loops
    pthread_create(&send_thread, NULL, send_message, NULL);
    pthread_create(&receive_thread, NULL, receive_message, NULL);

    // join is triggered when results are sent or received
    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);

    return 0;
}
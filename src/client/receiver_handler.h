#ifndef RECEIVER_HANDLER
#define RECEIVER_HANDLER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main_client.h"
#include "sender_handler.h"

#define SERVER_IP "104.168.153.49"
#define SERVER_PORT 25176 

void receive_message(struct Message *receivedMessage);

#endif
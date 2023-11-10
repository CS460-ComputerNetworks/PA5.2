#ifndef MAIN_CLIENT
#define MAIN_CLIENT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sender_handler.h"
#include "receiver_handler.h"

#define SERVER_IP "104.168.153.49"
#define SERVER_PORT 25176

#define STR_LEN 100

struct Message {
    int type;
    char senderName[STR_LEN];
    char content[STR_LEN];
} Message;


#endif
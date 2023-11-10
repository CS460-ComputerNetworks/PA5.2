#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "receiver_handler.h"

#define SERVER_IP "104.168.153.49"
#define SERVER_PORT 25176 

void *send_message(void *arg);
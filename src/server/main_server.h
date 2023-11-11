#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>

/* Preprocessor directives */
#define SERVER_ADDR "104.168.153.49" // loopback ip address
#define PORT 25176              // port the server will listen on

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 5       // number of pending connections in the connection queue
// Define constants for message types
#define JOIN 1
#define LEAVE 2
#define NOTE 3
#define SHUTDOWN 4
#define SHUTDOWN_ALL 5


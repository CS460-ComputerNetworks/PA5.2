#ifndef CHAT_NODE_H
#define CHAT_NODE_H

// header files
#include <stdlib.h>

#define MAX_STR_LEN 128

typedef struct ChatNode
   {
      unsigned ip:32; // Use exactly 4 bytes to represent the IP address
      int port;
      char *logicalName;
      struct ChatNode *nextNode;
   } ChatNode;

// prototypes
ChatNode createChatNodeLinkedList();

#endif
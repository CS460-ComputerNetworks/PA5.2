#ifndef CHAT_NODE_H
#define CHAT_NODE_H

#define MAX_STR_LEN 128
typedef struct ChatNode
   {
      int ip;
      int port;
      char logicalName[ MAX_STR_LEN ];
      struct ChatNode *nextNode;
   } ChatNode;

typedef enum { BAD_ARG_VAL = -1,
               JOIN, // 0
               LEAVE, // 1
               NOTE, // 2
               NOTE, // 3
               SHUTDOWN, // 4
               SHUTDOWN_ALL // 5
               } ;
#endif
#ifndef MESSAGE_H
#define MESSAGE_H

// header files
#include <stdlib.h>
#include "chat_node.h"

typedef enum { BAD_ARG_VAL = -1,
               JOIN,             // 0
               LEAVE,            // 1
               NOTE,             // 2
               NOTE,             // 3
               SHUTDOWN,         // 4
               SHUTDOWN_ALL      // 5
               } ;

typedef struct {
   ChatNode node;
   int messageType; // Use enumerated constants to represent
} MessageStruct;

// prototypes
void handle_message();
               
#endif
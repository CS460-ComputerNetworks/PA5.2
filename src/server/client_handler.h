// client_handler.h
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

void talk_to_client(void *arg);
int client_exists(int client_socket);
void add_client(int client_socket);
void remove_client(int client_socket);
char *get_message(int client_socket);
void send_message(int message_type, int client_socket, char *message);
void send_message_to_all(int message_type, int client_socket);

#endif // CLIENT_HANDLER_H

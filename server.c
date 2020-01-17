#include "networking.h"


void read_write(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(client_socket, buffer, sizeof(buffer));
    //Goes First
    read(client_socket, buffer, sizeof(buffer));
    printf("[server] received: [%s]\n", buffer);
  }
  close(client_socket);

  exit(0);


}

int main() {

  int listen_socket;
  int client_socket;
  char buffer[BUFFER_SIZE];

  //set of file descriptors to read from
  fd_set read_fds;

  listen_socket = server_setup();

  while (1) {

    //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds); //0 out fd set
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(listen_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(listen_socket + 1, &read_fds, NULL, NULL, NULL);

    //if listen_socket triggered select
    if (FD_ISSET(listen_socket, &read_fds)) {
     client_socket = server_connect(listen_socket);

    }//end listen_socket select

    read_write(client_socket);
}}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MAX_DATA_SIZE 16

int sendall(int socket, const char *buf, int *buf_len) {
  int total_sent = 0;        // How much we've sent
  int bytes_left = *buf_len; // How much we've left
  int n;
  while (total_sent < *buf_len) {
    n = send(socket, buf + total_sent, bytes_left, 0);
    if (n < 0) {
      break;
    }

    total_sent += n;
    bytes_left -= n;
  }

  // Return total amount sent
  *buf_len = total_sent;

  return n == -1 ? -1 : 0; // Was the last send call OK?
}

int main(void) {
  char buf[MAX_DATA_SIZE] = "Rafa";
  int len = strlen(buf);

  int sock = socket(AF_INET, SOCK_STREAM, PF_INET); // Fake socket
  if (sendall(sock, buf, &len) == -1) {
    fprintf(stderr, "Did not send all data\n");
    exit(EXIT_FAILURE);
  }

  printf("Sent all data!\n");

  exit(EXIT_SUCCESS);
}

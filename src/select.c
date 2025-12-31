#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

/*
 * add stdin to readfds
 * wait 2.5 seconds
 * then poll readfds to see if stdin is ready
 */

int main(void) {
  fd_set readfds;

  struct timeval tv;
  tv.tv_sec = 2;
  tv.tv_usec = 500000;

  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

  if (FD_ISSET(STDIN_FILENO, &readfds)) {
    printf("A key was pressed!\n");
  } else {
    printf("Timed out\n ");
  }

  exit(EXIT_SUCCESS);
}

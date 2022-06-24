#include <cstdio>
#include <cstdlib>

void DieWithError(const char *errorMessage) {
  perror(errorMessage);
  exit(EXIT_FAILURE);
}

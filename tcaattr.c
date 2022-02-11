#include "function.h"


//petit pgm pour etre en raw mode et voir ce que lon ecrit byte par byte

void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw);
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int main() {
  enableRawMode();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
      printf("%c [%d]\n", c, c);
  return 0;
}

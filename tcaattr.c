#include "function.h"


//petit pgm pour etre en raw mode et voir ce que lon ecrit byte par byte
// le flag ISIG permet de bloquer les signaux (gestion des ctrl)
// le I devant ISIG et ICANON provient de INPUT
//OPOST enleve le retour charriot pour le retablir il faudrait mettre \r avant le \n
//When BRKINT is turned on, a break condition will cause a SIGINT signal to be sent to the
//program, like pressing Ctrl-C. => pas trop compris linteret

void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw);
  //raw.c_oflag &= ~(OPOST);
  raw.c_iflag &= ~(BRKINT);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int main() {
  enableRawMode();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
      printf("%c [%d]\n", c, c);
  return 0;
}

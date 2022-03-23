#include "includes/function.h"

int main()
{
	int fd;

	fd = open("ok", O_CREAT | O_WRONLY | O_TRUNC, 00777);
	close (fd);
}
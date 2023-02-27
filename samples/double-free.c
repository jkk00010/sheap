#include <stdlib.h>

int main(void)
{
	char *ptr = malloc(1);
	free(ptr);
	free(ptr);
}

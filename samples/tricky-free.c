#include <stdlib.h>

void *allocate(void)
{
	return malloc(1);
}

void deallocate(void *ptr)
{
	free(ptr);
}

void moredeallocate(void *ptr)
{
	free(ptr);
}

int main(void)
{
	void *ptr = allocate();
	deallocate(ptr);
	moredeallocate(ptr);
}

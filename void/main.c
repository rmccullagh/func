#include <stdlib.h>
#include <stdio.h>

void fn()
{
	fprintf(stdout, "%s called\n", __FUNCTION__);
}

void (*function_table[4]) = {0};

int main()
{

	size_t i;
	for(i = 0; i < 4; i++) {

		function_table[i] = &fn;

	}
		

	function_table[0]();

	return 0;
}

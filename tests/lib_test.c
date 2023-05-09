#include <unistd.h>
#include <assert.h>
#include <minix/config.h>
#include <stdio.h>

int main()
{
	int my_amount = transfermoney(1, 0);
	assert(my_amount == INIT_BALANCE);
	printf("%d\n", my_amount);

	return 0;
}
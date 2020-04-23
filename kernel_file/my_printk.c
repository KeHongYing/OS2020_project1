#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_my_printk(char *messenge)
{
	printk("%s\n", messenge);
	return;
}

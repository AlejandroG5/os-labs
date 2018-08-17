/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

void simple_uptime(void);
void simple_systeminfo(void);

/* This function is called when the module is loaded. */
int simple_init(void)
{
        printk(KERN_INFO "Loading Module\n");
	simple_uptime();
	simple_systeminfo();
        return 0;
}

void simple_uptime()
{
	printk("Uptime: %d\n",(jiffies_to_msecs(get_jiffies_64())/1000));
}

void simple_systeminfo(){
	struct new_utsname *a= utsname();
	printk(a->sysname);
	printk(a->nodename);
	printk(a->release);
	printk(a->version);
	printk("Machine:  %s\n",a->machine);
}
/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


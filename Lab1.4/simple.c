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
typedef struct{
	int id;
	char *name;
	int age;
} student;
int counter=0;

void simple_uptime(void);
void simple_systeminfo(void);
void add_student(int id,char *name, int age);
void list_student(void);

/* This function is called when the module is loaded. */

student group[10];

int simple_init(void)
{
        printk(KERN_INFO "Loading Module\n");
	simple_uptime();
	simple_systeminfo();
	add_student(101,"Alejandro",21);
	add_student(123,"Ramon",20);
	list_student();
        return 0;
}

void simple_uptime()
{
	printk("Uptime: %d sec \n",(jiffies_to_msecs(get_jiffies_64())/1000));
}

void simple_systeminfo(){
	struct new_utsname *a= utsname();
	printk("Sysname:  %s\n",a->sysname);
	printk("Nodename:  %s\n",a->nodename);
	printk("Realease:  %s\n",a->release);
	printk("Version:  %s\n",a->version);
	printk("Machine:  %s\n",a->machine);
}

void add_student(int id,char *name,int age){
	group[counter].id=id;
	group[counter].name=name;
	group[counter].age=age;	
	counter++;
}

void list_student(){
	int a;
	for(a=0;a<counter;a++){
		printk("Students: %s\n Name: %s\n\tID: %d\n\tAge: %d\n"," ",group[a].name,group[a].id,group[a].age);
	}
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


/*As a user if we want to look into what the kernel is up to, we would need our application to read the data in kernel space.
But applications running in the user space can not access the data in the kernel space, in such situations the proc file system comes to rescue.
The proc file system is an interface between the kernel and the userspace. Every entry in the proc file system provides some information from the kernel.
The proc file system is also very useful when we want to debug a kernel module. While debugging we might want to know the values of various variables in
the module or may be the data that module is handling. In such situations we can create a proc entry for our selves and dump what ever data we want to 
look into in the entry.
The proc entry can also be used to pass data to the kernel by writing into the kernel, so there can be two kinds of proc entries
An entry that only reads data from the kernel space. An entry that reads as well as writes data into and from kernel space.

From "Linux Device driver"
*/


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include<linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>



int  len; 	/* lenght of data copied*/
int  temp;  /* number of temporary data copied*/
char *msg;  /*Point a region allocated in the kernel space by the kmalloc*/

/*
 * filp  -->  file pointer
 * buff  -->  pointer to the USER BUFFER holding the data to be written or the empty buffer where the newly read data should be placed
 * count -->  size of requested data transfer
 * offp  -->  pointer to the file posizione (offset from the beginning)
 */

ssize_t write_proc(struct file *filp, const char __user *buff, size_t count, loff_t *offp){

	copy_from_user(msg ,buff ,count); /*Copy data pointed by buff (USER SPACE) in msg (pointer to memory allocated in KERNEL SPACE), count is the size of copied data*/
	len = count;
	temp = len;

	return count;
}





ssize_t read_proc(struct file *filp, char __user *buff, size_t count, loff_t *offp){
/* until that count == 0 --> fill data pointed by msg (KERNEL SPACE) in the user buffer, buff (USER SPACE), temp = temporary data copied in the user buffer */
	if (count > temp){ 

		count = temp; 
	}

	temp = temp - count;
	copy_to_user(buff, msg, count);


	if(count == 0){
		temp = len;
	}

	return count;
}





static struct file_operations proc_fops ={
	.owner = THIS_MODULE,
	.read = read_proc,
	.write = write_proc
};


void create_new_proc_entry(void){

	proc_create("my_proc", 0, NULL, &proc_fops);
	msg = kmalloc( 10 * sizeof(char), GFP_KERNEL); /* Pointer to memory allocate in (KERNEL SPACE) for passing msg from userspace to kernel space and viceversa*/


}



int proc_init(void){

	create_new_proc_entry();
	printk(KERN_ALERT "Entry module\n");
	return 0;
}

void proc_cleanup(void){


	remove_proc_entry("my_proc", NULL);
	kfree(msg);
	printk(KERN_ALERT "Cleanup module\n");
}


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Tommaso Merciai");


module_init(proc_init);
module_exit(proc_cleanup);

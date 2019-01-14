#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>            /* File operations structure for(open/close, read/write)*/
#include <linux/cdev.h>          /* For setup char driver, makes cdev avaible*/
#include <linux/semaphore.h>     /* To access semaphore, to respect the principle of mutual exclusion (Mutex), 1 unlock (green)  0 lock (red)*/   
#include <asm/uaccess.h>          /* Copy from userspace to kernel space and vice versa function --> (copy_from_user, copy_to_user)*/

/* --> (1) */

/*Create a struct that rapresent our device*/
struct my_device{
    char data[200];
    struct semaphore sem;
}virtual_dev;

/*To register our device in the kernel space we need:*/

struct cdev *my_cdev;     /* Struct to register our char device*/
static int major;         /* Major number that rapresent the driver, instead of minor that rapresent the device */
static int minor = 0;     /* First generally is 0 */
static int ret;           /* Return*/
dev_t dev_n;              /* Hold major and minor number MAJOR(dev_n), MINOR(dev_n)*/
#define DEVICE_NAME "scottdevice"


/* --> (5) */

/*Definitions of the file operations method*/

/*Open Method*/
int device_open(struct inode *inode, struct file *filp){
    if(down_interruptible(&virtual_dev.sem) != 0){          /*Only one process can open the device by using semaphore*/
        printk(KERN_ALERT "Can not lock device during open\n");
        return -1;
    }

    printk(KERN_INFO "Device opened\n");
    return 0;

}

/*Write method*/
ssize_t device_write(struct file *filp, const char *buffer, size_t buffcount, loff_t *off_p){
    printk(KERN_INFO "Writing to the device\n");
    ret = copy_from_user(virtual_dev.data , buffer, buffcount); /*Send data from user to kernel space*/

    return ret;
}



/*Read method*/ 
ssize_t device_read(struct file *filp, char *buffer, size_t buffcount, loff_t *off_p){
    printk(KERN_INFO "Reading from the device\n");
    ret = copy_to_user(buffer ,virtual_dev.data ,buffcount); /*Copy from kernel space to the buffer of the user space  (copy_to_user(dest, from, sizetotransfer)*/

    return ret;
}


/*Close method*/
int device_close(struct inode *inode, struct file *filp){
    up(&virtual_dev.sem); /*Release mutex the we obtain by the open method (down), we release the mutex that we obtain with open sys call */
    printk(KERN_INFO "Device closed");
    return 0;
}





/* --> (4) */


/*Create file operation structure (f_ops): tell the kernel wich function call when user operates on our device*/
struct file_operations f_ops ={
    .owner = THIS_MODULE,       /*Preventing unloading of this module when operations are in use*/
    .open = device_open,        /*Points to method to call when opening the device*/
    .release = device_close,    /*Points to method to call when closing the device*/
    .write = device_write,      /*Points to method to call when writing to the device*/
    .read = device_read         /*Points to method to call when reading from the device*/
};


/* --> (2) */

/*Register our device to the kernel, need 2 step*/
static int driver_init(void){

/*Step(1) dinamic allocation of a major number*/
    ret = alloc_chrdev_region(&dev_n, minor, 1, DEVICE_NAME); 
    if(ret){
        printk(KERN_ALERT "Failed to allocate Major number\n");
        return ret;
    }
    
    major = MAJOR(dev_n);
    minor = MINOR(dev_n);

    printk(KERN_INFO "DEVICE --> %s,[ Major = %d ], [ minor  = %d ]\n",DEVICE_NAME, major, minor);
    printk(KERN_INFO "\tUSE --> \"mknod /dev/%s c %d %d\" to create device file\n", DEVICE_NAME, major, minor);

/*Step(2) allocate cdev structure (create cdev struct and add it to the kernel)*/

    my_cdev = cdev_alloc();            /*Create cdev structure*/
    my_cdev->ops = &f_ops;              /*File operations*/
    my_cdev->owner = THIS_MODULE;      

    ret = cdev_add(my_cdev, dev_n, 1); /*Add cdev to the kernel*/
    if(ret){
        printk(KERN_ALERT "Unable to add cdev to the kernel\n");
        return ret;
    }
    sema_init(&virtual_dev.sem, 1);    

    return 0;
}

/* --> (3) */

/*Unregister everyting in revers order*/
static void driver_cleanup(void){
    cdev_del(my_cdev);
    unregister_chrdev_region(dev_n, 1);
    printk(KERN_ALERT "Unload module\n");

}


MODULE_AUTHOR("Tommaso Merciai");
MODULE_LICENSE("Dual BSD/GPL");


module_init(driver_init);
module_exit(driver_cleanup);




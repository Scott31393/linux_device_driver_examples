#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/types.h>


/* Get Major and minor number for 4 char device driver example */

MODULE_AUTHOR("Tommaso Merciai");
MODULE_LICENSE("Dual BSD/GPL");


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* (Usually in prototipes.h) from here */


//Define
#define DEVICE_NAME "scott_char_dev"
#define BUFF_LEN  100

//Utilities
static int major = 0;
static int minor = 0;
static int n_devs = 4;



/*
 * Manipulate devices memory
 * 
 * In scull, each device (4) is a linked list of pointers, each of which points to a Scull_Dev structure. 
 * Each such structure can refer, by default, to at most four million bytes, through an array of intermediate pointers.
 * The released source uses an array of 1000 pointers to areas of 4000 bytes. We call each memory area a quantum and the array (or its length) a quantum set.
 * 
 * cit. "Linux device driver"
*/




/* Prototypes init and cleanup */
 

int chdev_init(void);
void chdev_cleanup(void);




// /////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Init and cleanup */

int chdev_init(void){

    int ret;
    dev_t dev = 0;
    printk(KERN_ALERT "Init module here\n");

    if(major){
        dev = MKDEV(major, minor);
        ret = register_chrdev_region(dev, n_devs, DEVICE_NAME);
    } else{
        ret = alloc_chrdev_region(&dev, minor, n_devs, DEVICE_NAME);
        major = MAJOR(dev);
    }
    if(ret < 0){
        printk(KERN_ALERT "Can not get a major and minor number\n");
    }
 
    printk(KERN_ALERT "MAJOR AND MINOR NUMBER ARE = %d, %d\n", MAJOR(dev), MINOR(dev));







    return 0;
}


void chdev_cleanup(void){
    dev_t devno = MKDEV(major, minor);

    unregister_chrdev_region(devno, n_devs);
    printk(KERN_ALERT "Clean up Module\n");

}

module_init(chdev_init);
module_exit(chdev_cleanup);


/*
 * Methods
 */
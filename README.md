# Linux device driver examples


![alt text](https://lwn.net/Kernel/LDD3/cover.gif) <br /> <br />
https://lwn.net/Kernel/LDD3/

Reading the book "Linux Device Driver [Third Edition]" I will publish examples on the chapters that I am reading, to put into practice the concepts explained.

## 1) Dynamic Allocation of Major Numbers

file --> alloc_major-number<br />

In this example we can see how to dynamically get major and minor numbers for 4 character devices driver. <br />
(Like scull example)

[Linux device driver]: https://www.xml.com/ldd/chapter/book/ch03.html <br />

## Build

Open Terminal (press `ctrl-t`)<br />

Get the repository:
`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />
`cd /alloc_major-number` <br /> 
`make` <br />

Dynamically linking the module to the kernel:<br />
`sudo insmod main.ko`<br />


Visualize messages contained by the kernel buffer on the stardard output of the OS :<br />
`dmesg`<br />


Remove kernel module:<br />
`sudo rmmod main.ko`<br />

## 2) Create /proc/my_proc Filesystem To Write and Read Data To/From Kernel Space

file --> proc_write_read <br />

In this example we create the new proc filesystem /proc/my_proc to write and read data to/from kernel space. <br />

As a user if we want to look into what the kernel is up to, we would need our application to read the data in kernel space.
But applications running in the user space can not access the data in the kernel space, in such situations the proc file system comes to rescue.
The proc file system is an interface between the kernel and the userspace. Every entry in the proc file system provides some information from the kernel.
The proc file system is also very useful when we want to debug a kernel module. While debugging we might want to know the values of various variables in
the module or may be the data that module is handling. In such situations we can create a proc entry for our selves and dump what ever data we want to 
look into in the entry.
The proc entry can also be used to pass data to the kernel by writing into the kernel, so there can be two kinds of proc entries
An entry that only reads data from the kernel space. An entry that reads as well as writes data into and from kernel space.

From "Linux Device driver", "Linux world blogspot".


## Build

Open Terminal: <br /> (press `ctrl-t`)<br />

Get the repository:<br />
`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />
`cd /alloc_major-number` <br /> 
`make` <br />

Dynamically linking the module to the kernel:<br />
`sudo insmod main.ko`<br />


Visualize messages contained by the kernel buffer on the stardard output of the OS :<br />
`dmesg`<br />

We the Kern alert log: "Entry module".<br />

Now we can play with our new /proc/my_proc. First we make the file readable, writable and executable by everyone using chmod 777: <br /> 

`sudo chmod 777 /proc/my_proc`

Now we can write data string to the file, like "hello", using echo in Terminal:

`echo "hello" > /proc/my_proc` 

And we can read that string using cat:

`cat /proc/my_proc`

After that "hello" strings appear in the Terminal console. To remove the loadable kernel module (LKM) press:

`sudo rmmod main.ko`

"Cleanup module" log appear on the dmesg log.



## 3) Create a Simple Character Device Driver /dev/scottdevice 

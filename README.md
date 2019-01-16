# Linux device driver examples


![alt text](https://lwn.net/Kernel/LDD3/cover.gif) <br /> <br />
https://lwn.net/Kernel/LDD3/

Reading the book "Linux Device Driver [Third Edition]" I will publish examples on the chapters that I am reading, to put into practice the concepts explained.

## 1) Dynamic Allocation of Major Numbers

file --> 1_alloc_major_number<br />

In this example we can see how to dynamically get major and minor numbers for 4 character devices driver. <br />
(Like scull example)

[Linux device driver]: https://www.xml.com/ldd/chapter/book/ch03.html <br />

## Build

Open Terminal (press `ctrl-t`)<br />

Get the repository:<br />

`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />

`cd /1_alloc_major-number` <br /> 

`make` <br />

Dynamically linking the module to the kernel:<br />

`sudo insmod main.ko`<br />


Visualize messages contained by the kernel buffer on the stardard output of the OS :<br />

`dmesg`<br />


Remove kernel module:<br />

`sudo rmmod main.ko`<br />

## 2) Create /proc/my_proc Filesystem To Write and Read Data To/From Kernel Space

file --> 2_proc_write_read <br />

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

Get the files from the repository:<br />

`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />

`cd /2_proc_write_read` <br />
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



## 3) Create a Simple Character Device Driver [/dev/scottdevice]

file --> 3_simply_chdvdriver <br />


In this example (play_with_simply_chdvdriver) we create a new character device driver, in the next example we how to write into the device and we see also how to read from this device<br />


## Build

Open Terminal: <br /> (press `ctrl-t`)<br />

Get the files from the repository:<br />

`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />

`cd /3_simply_chdvdriver` <br /> 

`make` <br />

Dynamically linking the module to the kernel:<br />
`sudo insmod main.ko`<br />


Visualize messages contained by the kernel buffer on the stardard output of the OS :<br />
`dmesg`<br />

We the Kern alert log: "DEVICE --> scottdevice,[ Major = 239 ], [ minor  = 0 ]".<br />

We make the character device file readable, writable and executable by everyone using chmod 777: <br /> 

`sudo chmod 777 /dev/scottdevice`

In the next example (4) we see how to play with this character device.

To remove the loadable kernel module (LKM) press:

`sudo rmmod main.ko`

"Unload module" log appear on the dmesg log.


## 4) Create a User space App [play] That Can Write/Read From/To The Simple Character Device Driver [/dev/scottdevice]

file--> 4_play_with_simply_chdvdriver

In this example we create a simple user application that can write or read data to/from the device created in the previous example: "/dev/scottdevice".

## Build


Open Terminal: <br /> (press `ctrl-t`)<br />

Get the files from the repository:<br />

`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />

`cd /4_play_with_simply_chdvdriver` <br /> 

`make` <br />


Now just execute it using:<br />

`./play` <br />

Terminal ask you if you want write to the character device that we have created, just press:

`w`

 or if you want read from the character device that we have created, just press press:

 `r`

 
## 5) Load And Remove Module using Shell Script

file --> 5_load_remove_module_shell <br />

Instead of the use of the following Terminal's commands:

`insmod`<br/>
`chmod`<br/>
`rmmod`<br/>
`mknod`<br/>
`etc..`<br/>

We can simply create a shell script, that does everything with a single command. In particular you can try my shell scripts to load and remove module from the Linux kernel.


## Use

Open Terminal: <br /> (press `ctrl-t`)<br />

Get the files from the repository:<br />

`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />

`cd /5_load_remove_module_shell` <br /> 

Then after we build the "module".ko, we can link/remove that to the kernel using these scripts after we have positioned that in the same folder of the module.
First we make these scipts readable, writable and executable by everyone using chmod 777.<br />

`sudo chmod 777 load_module` <br />

`sudo chmod 777 remove_module` <br />


Now to Load the "scottdevice" belonging to the "main".ko module just execute the load script:

`./load_module` <br />

To remove the module just press:

`./remove_module` <br />

To check if these scripts do the right, we can visualize the messages in the kernel buffer in the standard output using:

`dmesg` <br />


## 6) Learning (POSIX) Semaphore by Example

file --> 6_POSIX_semaphore_example <br />

In this pic we can this the use of (Posix) semaphore to archived the mutual exclusion.

![Alt text](./imgs/Sem.png?raw=true "Title")

* 1 -> Semaphore is initialized to 1 (using sem_init() function).
* 2 -> Process/Thread P_1 see the value of semaphore (set to 1) then can access to resource.
* 3 -> During the execution of the Process/Thread P_1, semaphore's value is flipped to 0 (using sem_wait() function).
* 4 -> When the Process/Thread P_1 finished semaphore's value is flipped again to 1 (using sem_post() function). In this way next Process/Thread can access to resources.

we can see more in the specification in the following example:

## Build


Open Terminal: <br /> (press `ctrl-t`)<br />

Get the files from the repository:<br />

`gitclone https://github.com/Scott31393/linux_device_driver_examples.git`<br />

`cd /6_POSIX_semaphore_example` <br /> 

`make` <br />


Now just execute it using:<br />

`./main` <br />
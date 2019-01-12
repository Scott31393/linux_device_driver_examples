# Linux device driver examples


## Dynamic Allocation of Major Numbers For a Character Device Driver
alloc_major-number<br />

In this example we can see how to dynamically get major and minor numbers for 4 character devices driver. <br />
(Like scull example)

[Linux device driver]: https://www.xml.com/ldd/chapter/book/ch03.html <br />

## Build

Open terminal (press `ctrl-t`)<br />

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

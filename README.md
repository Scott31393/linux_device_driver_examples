# Linux_device_driver_examples
Linux device examples

1) alloc_major-number (Dynamic Allocation of Major Numbers)<br />

In this example we can see how to dynamically get major and minor number for a character device driver.<br />

[link text itself]: https://www.xml.com/ldd/chapter/book/ch03.html <br />

# Build<br />
<br />
<br />
Open terminal (press `ctrl-t`):<br />
`gitclone` the repository<br />
`cd /alloc_major-number`<br />
`make`<br />

Dynamically linking the module to the kernel<br />
`sudo insmod main.ko`<br />
<br />
Visualize messages contained by the kernel buffer on the stardard output of the OS :<br />
`dmesg`<br />
<br />
Remove kernel module<br />
`sudo rmmod main.ko`<br />


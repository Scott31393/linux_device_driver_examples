#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEVICE "/dev/scottdevice" /*Device file name*/


int main(){
    int n_bytes;                      /*Rapresents Number of bytes */
    int file_des;                     /*Rapresents File description*/
    char command;                     /*Rapresent command for read and writing*/
    char w_buffer[100];               /*write buffer */
    char r_buffer[100];               /*read buffer */

    file_des = open( DEVICE, O_RDWR); /*Opern for reading and writing*/
    if(file_des == -1){
        printf( "file %s not exist or has been locked  by another process\n", DEVICE);
        exit(-1);
    }
    printf("r = read from the device \nw = write to the device\nEnter command:  ");
    scanf("%c", &command);

    switch(command){

/*Data transfer from user space to kernel space using the system call write*/
        case 'w':
            printf("Enter data: ");
            scanf(" %[^\n]", w_buffer);
            write(file_des, w_buffer,  sizeof(w_buffer));
            break;

        case 'r':
            read(file_des, r_buffer, sizeof(r_buffer));
            printf("device: %s\n", r_buffer);
            break;
        
        default:
            printf("Command not correct\n");
            break;

    }

    close(file_des);

    return 0;
}
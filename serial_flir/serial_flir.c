/*
 * ============================================================================
 *
 *       Filename:  serial_flir.c
 *
 *    Description:  sent command to flir camera to change the configures
 *
 *        Version:  
 *        Created:  
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xueqian Jin
 *   Organization:  nju
 *
 * ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include "crc.h"
#include "serial_flir.h"

int main(int argc, char *argv[])
{
    int fd;
    unsigned char cmd[128];

    fd = serial_init(2);
    printf("serial_initial succeed\n");

    cmd[0] = 0x00; cmd[1] = 0x05;  /* 0005 linear algorithm*/
    send_command(fd, AGC_TYPE, cmd, 2);
    

    cmd[0] = 0; cmd[1] = 0;  /* 0000 tail rejection percentage=0 */
    send_command(fd, TAIL_SIZE, cmd, 2);


    cmd[0] = 0; cmd[1] = 0;  /* set default*/
    send_command(fd, SET_DEFAULTS, cmd, 0);

    printf("end\n");

    close(fd);
}

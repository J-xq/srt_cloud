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
    //while(1)
    //{
      //  cmd[0] = 0x00; cmd[1] = 0x00;
      //  send_command(fd, READ_SENSOR, cmd, 2);
      //  usleep(1000000);
    //}

    //cmd[0] = 0x00; cmd[1] = 0x00;  
    //send_command(fd, FACTORY_DEFAULTS, cmd, 0);


    cmd[0] = 0x00; cmd[1] = 0x02;  //gain mode
    send_command(fd, GAIN_MODE, cmd, 2);
/*
    cmd[0] = 0x00; cmd[1] = 0x33;cmd[2] = 0x00; cmd[3] = 0x01;
    cmd[4] = 0x00; cmd[5] = 0x32;cmd[6] = 0x00; cmd[7] = 0x64;
    send_command(fd,GAIN_SWITCH_PARAMS, cmd, 8);
*/
    cmd[0] = 0x00; cmd[1] = 0x05;  //linear
    send_command(fd,AGC_TYPE,cmd,2);
    
    cmd[0] = 0x04; cmd[1] = 0x00; cmd[2] = 0x00; cmd[3] = 0x00;//SSO=0
    send_command(fd,AGC_TYPE,cmd,4);

    cmd[0] = 0x00; cmd[1] = 0x00;  //tail rejection percentage=0
    send_command(fd,TAIL_SIZE,cmd,2);
    
    cmd[0] = 0x00; cmd[1] = 0x00;  //ACE_CORRECT=0
    send_command(fd,ACE_CORRECT,cmd,2);

    cmd[0] = 0x00; cmd[1] = 0x00;  //DDE GAIN DISABLE
    send_command(fd,DDE_GAIN,cmd,2);

    cmd[0] = 0x00; cmd[1] = 0xff;  //AGC filter
    send_command(fd,AGC_FILTER,cmd,2);

    cmd[0] = 0x00; cmd[1] = 0x00;  //plateau level=0
    send_command(fd,PLATEAU_LEVEL,cmd,2);

    cmd[0] = 0; cmd[1] = 0;  
    send_command(fd, SET_DEFAULTS, cmd, 0);

    printf("end\n");

    close(fd);
}

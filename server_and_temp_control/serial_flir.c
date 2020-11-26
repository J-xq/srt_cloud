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

float gettemp()
{
    int fd;
    float FPA_TEMP;
    unsigned char cmd[128];

    fd = serial_init(2);
    
    cmd[0] = 0x00; cmd[1] = 0x00;
    FPA_TEMP=send_command(fd, READ_SENSOR, cmd, 2);
    close(fd);
    //printf("%f\n",FPA_TEMP);
    return FPA_TEMP;
}

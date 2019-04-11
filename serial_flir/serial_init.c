/*
 * ============================================================================
 *
 *       Filename:  serial_init.c
 *
 *    Description:  
 *
 *        Version:  
 *        Created:  
 *       Revision:  
 *       Compiler:  gcc
 *
 *         Author:  Xueqian Jin
 *   Organization:  nju
 *
 * ============================================================================
 */

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define	BAUDRATE B921600
speed_t bautratelist[] = {
    B9600, B19200, B57600, B115200, B460800, B921600
};

#define	DEV	"/dev/ttyUSB0"

int fdserial = -1;

int serial_init(int bb)
{
    int fd;
    struct termios newtio;
    speed_t br;

//    fd = open(DEV, O_RDWR | O_NOCTTY | O_NDELAY|O_NONBLOCK);
    fd = open(DEV, O_RDWR);
    if(fd < 0){
        printf("open %s error\n", DEV);
        return -1;
    }
    br = bautratelist[bb];

    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */
    //configure the serial port;
    cfsetspeed(&newtio, br);
    //	newtio.c_cflag |=CLOCAL|CREAD;  /*8N1*/
    newtio.c_cflag &= ~CSIZE; /* Mask the character size bits */
    newtio.c_cflag |= CS8; /* Select 8 data bits */
    newtio.c_cflag &= ~PARENB;
    newtio.c_cflag &= ~CSTOPB;
    newtio.c_cflag &= ~CRTSCTS;//disable hardware flow control;
    newtio.c_lflag &= ~ICANON;/*raw input*/
    //	newtio.c_lflag &= ~(ISIG);/*raw input*/
    //	newtio.c_oflag &= ~OPOST; /*raw output*/
    tcflush(fd,TCIFLUSH);//clear input buffer
    newtio.c_cc[VTIME] = 10; /* inter-character timer unused */
    newtio.c_cc[VMIN] = 1; /* blocking read until 0 character arrives */

    tcsetattr(fd, TCSANOW, &newtio);
    fdserial = fd;
    return fd;
}

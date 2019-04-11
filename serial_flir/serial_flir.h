/*
 * ============================================================================
 *
 *       Filename:  serial_flir.h
 *
 *    Description:  
 *
 *        Version:  
 *        Created:  
 *       Revision:  none
 *       Compiler: 
 *
 *         Author:  Xueqian Jin
 *   Organization:  nju
 *
 * ============================================================================
 */

#ifndef _SERIAL_FLIR_H
#define _SERIAL_FLIR_H

#define NO_OP               0x00
#define SET_DEFAULTS        0x01
#define CAMERA_RESET        0x02
#define FACTORY_DEFAULTS    0x03
#define GET_SERIAL_NUMBER   0x04
#define GET_VERSION         0x05
#define BAUD_RATE           0x07
#define AGC_TYPE            0x13
#define TAIL_SIZE           0x1b

#define READ_SENSOR         0x20

#define DIGITAL_OUTPUT_MODE 0x12
#define SERIAL_NUMBER       0x65
#define CAMERA_PART         0x66
#define SHUTTER_POSITION    0x79
#   define  OPEN               0
#   define  CLOSE              1

#define TRANSFER_FRAME      0x82

#define MEMORY_STATUS       0xc4
#define READ_MEMORY         0xd2
#define ERASE_MEMORY_BLOCK  0xd4
#define GET_NV_MEMORY_SIZE  0xd5
#define GET_MEMORY_ADDRESS  0xd6

int serial_init(int);
int send_command(int fd, unsigned char CODE, char *data, int ncmd);

#endif

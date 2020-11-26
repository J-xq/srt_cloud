/*
 * ============================================================================
 *
 *       Filename:  send_command.c
 *
 *    Description:  
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
#include <string.h>
#include <unistd.h>
#include "crc.h"
#include "serial_flir.h"

float send_command(int fd, unsigned char CODE, char *data, int ncmd)
{
    int i, cnt;
    float FPA_TEMP;
    unsigned short crc;
    unsigned char cmd[128];

    cmd[0] = 0x6e;  /* process code */
    cmd[1] = 0;     /* status */
    cmd[2] = 0;     /* reserved */
    cmd[3] = CODE;
    cmd[4] = 0;     /* byte count MSB */
    cmd[5] = ncmd;  /* byte count LSB */

    crc = crc_ccitt(cmd, 6);  /* CRC1 */
    cmd[6] = (unsigned char)(crc >> 8);
    cmd[7] = (unsigned char)(crc & 0xff);

    for (i = 0; i < ncmd; i++)
        cmd[8 + i] = data[i];

    crc = crc_ccitt(cmd, 8 + ncmd);  /* CRC2 */
    cmd[8 + ncmd] = (unsigned char)(crc >> 8);
    cmd[9 + ncmd] = (unsigned char)(crc & 0xff);

    write(fd, cmd, 10 + ncmd);
    usleep(15000);
    cnt = read(fd, cmd, 128);
/*
    switch (cmd[1]) {
    case 0:
        printf("MESSAGE_RECEIVED\n");
        break;
    case 2:
        printf("NOT_READY\n");
        break;
    case 3:
        printf("RANGE_ERROR\n");
        break;
    case 4:
        printf("CHECKSUM_ERROR\n");
        break;
    case 5:
        printf("UNDEFINED_PROCESS_ERROR\n");
        break;
    case 6:
        printf("UNDEFINED_FUNCTION_ERROR\n");
        break;
    case 7:
        printf("TIMEOUT_ERROR\n");
        break;
    case 9:
        printf("BYTE_COUNT_ERROR\n");
        break;
    case 10:
        printf("FEATURE_NOT_ENABLED\n");
        break;
    default:
        printf("UNKNOWN ERROR: code:%02X, status:%02X\n", CODE, cmd[1]);
        break;
    }
*/
    FPA_TEMP=(cmd[8]*256+cmd[9])/10.0;
    return FPA_TEMP;
}

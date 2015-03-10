/*
 * NetComm.h
 *
 *  Created on: Mar 6, 2015
 *      Author: Anirudh Bagde
 */

#ifndef ROBOT_2015_NETCOMM_H_
#define ROBOT_2015_NETCOMM_H_

#include <stdint.h>

const int NETCOMM_RECVPORT = 6800;

// Little-endian on Galileo (x86)
struct __attribute__((__packed__)) ControlData {
    unsigned int forward :1;
    unsigned int reverse :1;
    unsigned int left :1;
    unsigned int right :1;
    unsigned short crc16;
};

class NetComm {
public:
    NetComm();
    ~NetComm();

    bool getData(ControlData* data);

private:
    int recvSock;
};

#endif /* ROBOT_2015_NETCOMM_H_ */

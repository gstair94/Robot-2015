/*
 * NetComm.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: Anirudh Bagde
 */

#include "NetComm.h"
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "crc-16.h"

NetComm::NetComm() {
    recvSock = socket(AF_INET, SOCK_DGRAM, 0);
    int reuse = 1;
    setsockopt(recvSock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(NETCOMM_RECVPORT);
    bind(recvSock, (sockaddr*) &addr, sizeof(addr));
    fcntl(recvSock, F_SETFL, O_NONBLOCK);
}

NetComm::~NetComm() {
    close(recvSock);
}

bool NetComm::getData(ControlData* data) {
    int size = sizeof(ControlData);
    bzero(data, size);
    int len = recvfrom(recvSock, data, size, 0, NULL, NULL);
    if (len < size) {
        return false;
    }
    unsigned short crc16Check = crc16((unsigned char*) data,
            sizeof(ControlData) - sizeof(unsigned short));
    if(crc16Check != data->crc16) {
        return false;
    }
    return true;
}

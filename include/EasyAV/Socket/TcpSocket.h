//
// Created by cx on 2018/11/8.
//

#ifndef EASYAV_TCPSOCKET_H
#define EASYAV_TCPSOCKET_H

#include <stdio.h>

namespace EasyAV {

    class TcpSocket {
    public:
        TcpSocket();

        virtual ~TcpSocket();

        ssize_t recv(void *buf, size_t len);

        ssize_t send(void *buf, size_t len);
    private:
        int mHandle;
    };

}//namespace EasyAV

#endif //EASYAV_TCPSOCKET_H

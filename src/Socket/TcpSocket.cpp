//
// Created by cx on 2018/11/8.
//

#include "EasyAV/Socket/TcpSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "EasyAV/Util/EasyLog.h"

#define MODULE_TAG "TcpSocket"

namespace EasyAV {

    TcpSocket::TcpSocket() : mHandle(0) {
        mHandle = ::socket(AF_INET, SOCK_STREAM, 0);
    }

    TcpSocket::~TcpSocket() {
        ::shutdown(mHandle, SHUT_RDWR);
    }

    ssize_t TcpSocket::recv(void *buf, size_t len) {
        return ::recv(mHandle, buf, len, 0);
    }

    ssize_t TcpSocket::send(void *buf, size_t len) {
        return ::send(mHandle, buf, len, 0);
    }

}//namespace EasyAV
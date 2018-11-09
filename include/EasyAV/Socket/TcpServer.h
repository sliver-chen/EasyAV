//
// Created by cx on 2018/11/8.
//

#ifndef EASYAV_TCPSERVER_H
#define EASYAV_TCPSERVER_H

#include "EasyAV/Socket/TcpSocket.h"

namespace EasyAV {

    class TcpServer : public TcpSocket {
    public:
        TcpServer() {}

        virtual ~TcpServer() {}
    private:

    };

}//namespace EasyAV

#endif //EASYAV_TCPSERVER_H

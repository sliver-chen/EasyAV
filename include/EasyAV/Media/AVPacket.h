#ifndef EASYAV_PACKET_H
#define EASYAV_PACKET_H

#include "EasyAV/Util/EasyUtil.h"

namespace EasyAV
{

    class AVPacket {
    public:
        AVPacket();

        AVPacket(unsigned char *compressData, size_t compressDataSize);

        AVPacket(const AVPacket &other);

        virtual ~AVPacket();

        AVPacket& operator= (const AVPacket &other);

        void appendBuffer(unsigned char *appendData, size_t appendDataSize);
    private:
        unsigned char *_CompressData;
        size_t _CompressDataSize;
    };

} //namespace EasyAV

#endif //EASYAV_PACKET_H
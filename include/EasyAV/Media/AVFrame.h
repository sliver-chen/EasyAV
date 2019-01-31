#ifndef EASYAV_FRAME_H
#define EASYAV_FRAME_H

#include "EasyAV/Util/EasyUtil.h"

namespace EasyAV {

    class AVFrame {
    public:
        AVFrame();

        AVFrame(unsigned char *rawData, size_t rawDataSize);

        AVFrame(const AVFrame &other);

        virtual ~AVFrame();

        AVFrame& operator=(const AVFrame& other);
    private:
        unsigned char *_RawData;
        size_t _RawDataSize;
    };

} //namespace EasyAV

#endif //EASYAV_FRAME_H
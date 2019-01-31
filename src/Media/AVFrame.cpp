#include "EasyAV/Media/AVFrame.h"

namespace EasyAV {

    AVFrame::AVFrame() : _RawData(nullptr),
                         _RawDataSize(0)
    {

    }

    AVFrame::AVFrame(unsigned char *rawData, size_t rawDataSize)
    {
        _RawDataSize = rawDataSize;
        _RawData = new unsigned char [_RawDataSize];
        ::memcpy(_RawData, rawData, _RawDataSize);
    }

    AVFrame::AVFrame(const AVFrame &other)
    {
        _RawDataSize = other._RawDataSize;
        _RawData = new unsigned char [_RawDataSize];
        ::memcpy(_RawData, other._RawData, _RawDataSize);
    }

    AVFrame::~AVFrame()
    {
        SAFE_DELETE_ARRAY(_RawData);
    }

    AVFrame& AVFrame::operator=(const AVFrame &other)
    {
        SAFE_DELETE_ARRAY(_RawData);
        _RawDataSize = other._RawDataSize;
        _RawData = new unsigned char [_RawDataSize];
        ::memcpy(_RawData, other._RawData, _RawDataSize);
        return *this;
    }

} //namespace EasyAV
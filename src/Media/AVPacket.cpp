#include "EasyAV/Media/AVPacket.h"

namespace EasyAV
{
    AVPacket::AVPacket() : _CompressData(nullptr),
                           _CompressDataSize(0)
    {

    }

    AVPacket::AVPacket(unsigned char *compressData, size_t compressDataSize)
    {
        _CompressDataSize = compressDataSize;
        _CompressData = new unsigned char [_CompressDataSize];
        ::memcpy(_CompressData, compressData, _CompressDataSize);
    }

    AVPacket::AVPacket(const AVPacket &other)
    {
        _CompressDataSize = other._CompressDataSize;
        _CompressData = new unsigned char[_CompressDataSize];
        ::memcpy(_CompressData, other._CompressData, _CompressDataSize);
    }

    AVPacket::~AVPacket()
    {
        SAFE_DELETE_ARRAY(_CompressData);
    }

    AVPacket& AVPacket::operator=(const AVPacket &other)
    {
        SAFE_DELETE_ARRAY(_CompressData);
        _CompressDataSize = other._CompressDataSize;
        _CompressData = new unsigned char[_CompressDataSize];
        ::memcpy(_CompressData, other._CompressData, _CompressDataSize);
        return *this;
    }

    void AVPacket::appendBuffer(unsigned char *appendData, size_t appendDataSize)
    {
        size_t originDataSize = _CompressDataSize;
        unsigned char *tmpBuffer = new unsigned char[_CompressDataSize];
        ::memcpy(tmpBuffer, _CompressData, _CompressDataSize);

        SAFE_DELETE_ARRAY(_CompressData);
        _CompressDataSize += appendDataSize;
        _CompressData = new unsigned char[_CompressDataSize];
        ::memcpy(_CompressData, tmpBuffer, originDataSize);
        ::memcpy(_CompressData + originDataSize, appendData, appendDataSize);
    }

} // EasyAV

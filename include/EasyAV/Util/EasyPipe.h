//
// Created by cx on 2018/11/29.
//

#ifndef EASYAV_EASYPIPE_H
#define EASYAV_EASYPIPE_H

#include <unistd.h>
#include <errno.h>
#include <string.h>

namespace EasyAV {
    class EasyPipe {
    public:
        EasyPipe();

        virtual ~EasyPipe();

        bool init(bool blocked = false);

        ssize_t read(void *buf, size_t count);

        ssize_t write(const void *buf,  size_t count);

        int getReadHandle() const {return mPipeFields[0];}

        int getWriteHandle() const {return mPipeFields[1];}
    private:
        void closePipe();
    private:
        int mPipeFields[2];
    };
} //namespace EasyAV

#endif //EASYAV_EASYPIPE_H

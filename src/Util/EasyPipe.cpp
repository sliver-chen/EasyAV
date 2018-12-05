//
// Created by cx on 2018/11/29.
//

#include "EasyAV/Util/EasyPipe.h"
#include "EasyAV/Util/EasyUtil.h"

#define MODULE_TAG "EasyPipe"

namespace EasyAV {
    EasyPipe::EasyPipe() {

    }

    EasyPipe::~EasyPipe() {
        closePipe();
    }

    bool EasyPipe::init(bool blocked) {
        if (::pipe(mPipeFields) != 0) {
            EasyLogErr(MODULE_TAG, "failed to generate pipe error %d %s", errno, strerror(errno));
            return false;
        }

        if (blocked) {
            setNoBlocked(mPipeFields[0], true);
            setNoBlocked(mPipeFields[1], false);
        }

        return true;
    }

    ssize_t EasyPipe::read(void *buf, size_t count) {
        return ::read(mPipeFields[0], buf, count);
    }

    ssize_t EasyPipe::write(const void *buf, size_t count) {
        return ::write(mPipeFields[1], buf, count);
    }

    void EasyPipe::closePipe() {
        ::close(mPipeFields[0]);
        ::close(mPipeFields[1]);
    }
} //namespace EasyAV
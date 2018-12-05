//
// Created by cx on 2018/11/29.
//

#include "EasyAV/Util/EasyUtil.h"
#include <sys/ioctl.h>

#define MODULE_TAG "EasyUtil"

namespace EasyAV {
    int setNoBlocked(int sock, bool noblock) {
        int ul = noblock;
        int ret = ioctl(sock, FIONBIO, &ul);
        if (ret == -1) {
            EasyLogErr(MODULE_TAG, "failed to set fd non-block");
        }

        return ret;
    }
} //namespace EasyAV
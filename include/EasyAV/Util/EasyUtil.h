//
// Created by cx on 2018/11/29.
//

#ifndef EASYAV_EASYUTIL_H
#define EASYAV_EASYUTIL_H

#include "EasyAV/Util/EasyLog.h"
#include "EasyAV/Util/EasyPipe.h"

#define SAFE_DELETE(x) {if(x){delete x;x=nullptr;}}
#define SAFE_DELETE_ARRAY(x) {if(x){delete[] x;x=nullptr;}}

namespace EasyAV {
    int setNoBlocked(int sock, bool noblock);
} //namespace EasyAV

#endif //EASYAV_EASYUTIL_H

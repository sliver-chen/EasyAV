//
// Created by cx on 2018/11/9.
//

#include "EasyAV.h"
#include <signal.h>

#define TEST_TAG "UtilTest"

using namespace EasyAV;

void LogTest() {
    EasyLogDbg(TEST_TAG, "LogDbg");
    EasyLogErr(TEST_TAG, "LogErr");
}

void PipeTest() {
    EasyPipe pipe;

    if (!pipe.init()) {
        EasyLogErr(TEST_TAG, "failed to init pipe");
        return;
    }

    if (::fork() == 0) {
        char buf[1024];
        int bytes = pipe.read(buf, sizeof(buf));
        EasyLogErr(TEST_TAG, "recv %d bytes %s", bytes, buf);
        return;
    } else {
        char buf[2014] = "msg from pipe";
        pipe.write(buf, sizeof(buf));
        EasyLogErr(TEST_TAG, "pipe send msg");
        return;
    }
}

int main(int argc, char **argv) {
    LogTest();

    PipeTest();

    return 0;
}
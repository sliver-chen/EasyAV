#include "EasyAV.h"
#include <signal.h>

#define TEST_TAG "EventTest"

using namespace EasyAV;

void EventTest() {
    signal(SIGINT, [](int){
        EasyLogDbg(TEST_TAG, "shut down");
        Event::instance()->shutdown();
        Event::Destroy();
    });

    if (!Event::instance()->init()) {
        EasyLogErr(TEST_TAG, "failed to init event loop");
        return;
    }

    Event::instance()->runEventLoop();
}

int main(int argc, char **argv) {
    EasyLogDbg(TEST_TAG, "test start");
    EventTest();

    getchar();
    EasyLogDbg(TEST_TAG, "test exit");
    return 0;
}
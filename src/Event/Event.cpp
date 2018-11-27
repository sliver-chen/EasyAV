//
// Created by cx on 2018/11/22.
//

#include "EasyAV/Event/Event.h"
#include "EasyAV/Util/EasyLog.h"

#define MODULE_TAG "Event"

namespace EasyAV {
    Event::Event() {

    }

    Event::~Event() {

    }

    Event* Event::instance() {
        static Event *context(new Event);
        return context;
    }

    bool Event::addEvent(int fd, EasyAV::EventType type, EventCB cb) {
        EventItem item;
        item.fd = fd;
        item.type = type;
        item.cb = cb;
        mEventMaps.emplace(fd, item);
    }

    bool Event::delEvent(int fd) {
        mEventMaps.erase(fd);
    }

    bool Event::runEventLoop(bool isBlocked) {
        if (isBlocked) {

        } else {
            mEventLoopThread = new std::thread(&Event::runEventLoop, this, true);
        }
    }
} //namespace EasyAV
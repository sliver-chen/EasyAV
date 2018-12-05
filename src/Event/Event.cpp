//
// Created by cx on 2018/11/22.
//

#include "EasyAV/Event/Event.h"
#include "EasyAV/Util/EasyUtil.h"

#define MODULE_TAG "Event"

namespace EasyAV {
    Event::Event() {
        mExitLoop = false;
        mEventThreadID = std::this_thread::get_id();
    }

    Event::~Event() {

    }

    Event* Event::instance() {
        static Event *context(new Event);
        return context;
    }

    void Event::Destroy() {
        delete Event::instance();
    }

    bool Event::init() {
        if (!mPipe.init(true)) {
            EasyLogErr(MODULE_TAG, "failed to init EasyPipe");
            return false;
        }

        return true;
    }

    void Event::addEvent(int fd, EasyAV::EventType type, EventCB cb) {
        EventItem item;
        item.fd = fd;
        item.cmd = EventAdd;
        item.cb = cb;
        item.type = type;

        if (isEventThread()) {
            std::lock_guard<std::mutex> lock(mEventMapLock);
            mEventMaps.emplace(fd, item);
        } else {
            mPipe.write(&item, sizeof(item));
        }
    }

    void Event::delEvent(int fd) {
        if (isEventThread()) {
            std::lock_guard<std::mutex> lock(mEventMapLock);
            mEventMaps.erase(fd);
        } else {
            EventItem item;
            item.fd = fd;
            item.cmd = EventDel;
            item.cb = nullptr;
            item.type = EventIDLE;
            mPipe.write(&item, sizeof(item));
        }
    }

    void Event::runEventLoop(bool isBlocked) {
        int ret = 0;
        int maxHandle = 0;
        std::list<EventCB> eventList;
        if (isBlocked) {
            for (;;) {
                FD_ZERO(&mSetRead);
                FD_ZERO(&mSetWrite);
                FD_ZERO(&mSetError);
                FD_SET(mPipe.getReadHandle(), &mSetRead);
                maxHandle = mPipe.getReadHandle();
                {
                    std::lock_guard<std::mutex> lock(mEventMapLock);
                    for (auto &pr : mEventMaps) {
                        if (pr.first > maxHandle) {
                            maxHandle = pr.first;
                        }
                        if (pr.second.type & EventRead) {
                            FD_SET(pr.first, &mSetRead);
                        }
                        if (pr.second.type & EventWrite) {
                            FD_SET(pr.first, &mSetWrite);
                        }
                        if (pr.second.type & EventError) {
                            FD_SET(pr.first, &mSetError);
                        }
                    }
                }

                if (mExitLoop)
                    break;
                EasyLogDbg(MODULE_TAG, "select I/O event");
                ret = ::select(maxHandle + 1, &mSetRead, &mSetWrite, &mSetError, NULL);
                if (ret <= 0) {
                    EasyLogErr(MODULE_TAG, "failed to select I/O due to %d %s", errno, strerror(errno));
                    continue;
                } else {
                    EasyLogDbg(MODULE_TAG, "get event");

                    // handle pipe event
                    if (FD_ISSET(mPipe.getReadHandle(), &mSetRead)) {
                        EasyLogDbg(MODULE_TAG, "get pipe event");
                        if (!handlePipeEvent()) {
                            EasyLogDbg(MODULE_TAG, "event loop get exit signal");
                            break;
                        }
                        if (ret == 1) {
                            continue;
                        }
                    }

                    {
                        std::lock_guard<std::mutex> lock(mEventMapLock);
                        for (auto &pr : mEventMaps) {
                            if (FD_ISSET(pr.first, &mSetRead)) {
                                eventList.push_back(pr.second.cb);
                            }
                            if (FD_ISSET(pr.first, &mSetWrite)) {
                                eventList.push_back(pr.second.cb);
                            }
                            if (FD_ISSET(pr.first, &mSetError)) {
                                eventList.push_back(pr.second.cb);
                            }
                        }
                    }

                    for (auto &pr : eventList) {
                        pr();
                    }
                    eventList.clear();
                }
            }
        } else {
            mEventLoopThread = new std::thread(&Event::runEventLoop, this, true);
        }
    }

    void Event::signalExit() {
        EasyLogDbg(MODULE_TAG, "send signal enter");
        mExitLoop = true;

        EventItem item;
        item.fd = 0;
        item.cmd = EventExit;
        item.type = EventIDLE;
        item.cb = nullptr;

        mPipe.write(&item, sizeof(item));
        EasyLogDbg(MODULE_TAG, "send signal exit");
    }

    void Event::shutdown() {
        signalExit();
        if (mEventLoopThread) {
            mEventLoopThread->join();
            SAFE_DELETE(mEventLoopThread);
        }
    }

    bool Event::isEventThread() const {
        return std::this_thread::get_id() == mEventThreadID;
    }

    bool Event::handlePipeEvent() {
        bool ret = true;
        EventItem item;
        mPipe.read(&item, sizeof(EventItem));
        switch (item.cmd) {
            case EventAdd : {
                std::lock_guard<std::mutex> lock(mEventMapLock);
                mEventMaps.emplace(item.fd, item);
            } break;
            case EventDel : {
                std::lock_guard<std::mutex> lock(mEventMapLock);
                mEventMaps.erase(item.fd);
            } break;
            case EventExit : {
                ret = false;
            } break;
            default :
                break;
        }
        return ret;
    }
} //namespace EasyAV
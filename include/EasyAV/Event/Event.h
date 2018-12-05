//
// Created by cx on 2018/11/22.
//

#ifndef EASYAV_EVENT_H
#define EASYAV_EVENT_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#include <list>
#include <mutex>
#include <vector>
#include <thread>
#include <functional>
#include <unordered_map>

#include "EasyAV/Util/EasyPipe.h"

namespace EasyAV {

    typedef std::function<void()> EventCB;

    enum EventType {
        EventRead  = 1 << 0,
        EventWrite = 1 << 1,
        EventError = 1 << 2,
        EventIDLE  = 1 << 3,
    };

    enum EventCmd {
        EventAdd = 0,
        EventDel,
        EventExit,
    };

    typedef struct EventItem_{
        int fd;
        EventCB cb;
        EventCmd cmd;
        EventType type;
    } EventItem;

    class Event {
    public:
        Event();

        virtual ~Event();

        static Event *instance();

        static void Destroy();

        bool init();

        void addEvent(int fd, EventType type, EventCB);

        void delEvent(int fd);

        void runEventLoop(bool isBlocked = false);

        void shutdown();
    private:
        bool isEventThread()const;

        bool handlePipeEvent();

        void signalExit();
    private:
        bool mExitLoop;

        std::thread::id mEventThreadID;

        fd_set mSetRead;
        fd_set mSetWrite;
        fd_set mSetError;

        std::vector<int> mSetVectors;
        std::thread *mEventLoopThread;
        std::mutex mEventMapLock;
        std::unordered_map<int, EventItem> mEventMaps;

        EasyPipe mPipe;
    };

} //namespace EasyAV

#endif //EASYAV_EVENT_H

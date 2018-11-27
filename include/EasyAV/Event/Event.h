//
// Created by cx on 2018/11/22.
//

#ifndef EASYAV_EVENT_H
#define EASYAV_EVENT_H

#include <sys/select.h>
#include <vector>
#include <thread>
#include <functional>
#include <unordered_map>

namespace EasyAV {

    typedef std::function<void(int event)> EventCB;

    enum EventType {
        EventRead  = 1 << 0,
        EventWrite = 1 << 1,
        EventError = 1 << 2,
    };

    typedef struct EventItem_{
        int fd;
        EventType type;
        EventCB cb;
    }EventItem;

    class Event {
    public:
        Event();

        virtual ~Event();

        static Event *instance();

        bool addEvent(int fd, EventType type, EventCB);

        bool delEvent(int fd);

        bool runEventLoop(bool isBlocked = false);
    private:
        fd_set *mSetRead;
        fd_set *mSetWrite;
        fd_set *mSetError;

        std::vector<int> mSetVectors;
        std::thread *mEventLoopThread;
        std::unordered_map<int, EventItem> mEventMaps;
    };

} //namespace EasyAV

#endif //EASYAV_EVENT_H

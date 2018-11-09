//
// Created by cx on 2018/11/8.
//

#ifndef EASYAV_EASYLOG_H
#define EASYAV_EASYLOG_H

#ifdef __cplusplus
extern "C" {
#endif

    void EasyLogDbg(const char *tag,const char *fmt,...);
    void EasyLogErr(const char *tag,const char *fmt,...);

#ifdef __cplusplus
};//extern "C"
#endif

#endif //EASYAV_EASYLOG_H

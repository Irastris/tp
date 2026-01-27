#ifndef M_DO_M_DO_DVD_THREAD_H
#define M_DO_M_DO_DVD_THREAD_H

#include <iostream>

#include "m_Do/m_Do_ext.h"
#include "f_pc/f_pc_node.h"
#include "JSystem/JKernel/JKRExpHeap.h"

// TODO: Not originally included directly
#include <dolphin/types.h>

typedef void* (*mDoDvdThd_callback_func)(void*);

class mDoDvdThd_command_c : public node_class {
public:
    bool mIsDone;
public:
    virtual ~mDoDvdThd_command_c();
    mDoDvdThd_command_c();
    inline s32 sync() { return mIsDone; }
    inline void destroy() { delete this; }
    virtual s32 execute() = 0;
};

class mDoDvdThd_param_c {
public:
    mDoDvdThd_param_c();
    void kick();
    s32 waitForKick();
    mDoDvdThd_command_c* getFirstCommand();
    void addition(mDoDvdThd_command_c*);
    void cut(mDoDvdThd_command_c*);
    void mainLoop();

private:
    // OSMessageQueue mMessageQueue;
    void* mMessageQueueMessages;
    node_list_class mNodeList;
    // OSMutex mMutext;
};

class mDoDvdThd_callback_c : public mDoDvdThd_command_c {
public:
    virtual ~mDoDvdThd_callback_c();
    mDoDvdThd_callback_c(mDoDvdThd_callback_func, void*);
    static mDoDvdThd_callback_c* create(mDoDvdThd_callback_func, void*);
    virtual s32 execute();

private:
    mDoDvdThd_callback_func mFunction;
    void* mData;
    void* mResult;
};

struct mDoDvdThdStack {
    u8 stack[4096];
} ATTRIBUTE_ALIGN(16);

struct mDoDvdThd {
    static s32 main(void*);
    static void create(s32);
    static void suspend();

    // static OSThread l_thread;
    static mDoDvdThdStack l_threadStack;
    static mDoDvdThd_param_c l_param;

    static u8 verbose;
    static bool SyncWidthSound;
    static u8 Report_DVDRead;
};

#endif

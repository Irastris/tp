#ifndef JKRPLATFORM_H
#define JKRPLATFORM_H

#include <chrono>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <new>

#include <dolphin/types.h>

#include "global.h"

typedef u64 JKRTick;

inline JKRTick JKRGetTick() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(
        high_resolution_clock::now().time_since_epoch()
    ).count();
}

inline u64 JKRTicksToMilliseconds(JKRTick ticks) {
    return ticks / 1000000ULL;
}

inline u64 JKRTicksToMicroseconds(JKRTick ticks) {
    return ticks / 1000ULL;
}

inline JKRTick JKRMillisecondsToTicks(u64 ms) {
    return ms * 1000000ULL;
}

class JKRMutex {
public:
    JKRMutex() = default;
    ~JKRMutex() = default;

    // Non-copyable
    JKRMutex(const JKRMutex&) = delete;
    JKRMutex& operator=(const JKRMutex&) = delete;

    void lock()   { mMutex.lock(); }
    void unlock() { mMutex.unlock(); }
    bool try_lock() { return mMutex.try_lock(); }

    std::mutex& native_handle() { return mMutex; }

private:
    std::mutex mMutex;
};

class JKRMutexLock {
public:
    explicit JKRMutexLock(JKRMutex& mutex) : mMutex(mutex) {
        mMutex.lock();
    }
    ~JKRMutexLock() {
        mMutex.unlock();
    }

    // Non-copyable
    JKRMutexLock(const JKRMutexLock&) = delete;
    JKRMutexLock& operator=(const JKRMutexLock&) = delete;

private:
    JKRMutex& mMutex;
};

inline void JKRMemcpy(void* dst, const void* src, size_t size) {
    std::memcpy(dst, src, size);
}

inline void JKRMemset(void* dst, int value, size_t size) {
    std::memset(dst, value, size);
}

#ifndef DECL_WEAK
#define DECL_WEAK __attribute__((weak))
#endif

#endif

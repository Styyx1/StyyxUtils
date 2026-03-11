//
// Created by styyx on 11/03/2026.
//

#pragma once
#include <windows.h>
#include <shared_mutex>

namespace StyyxUtil::DBGUtil
{
#ifdef NDEBUG
    struct ScopedSharedLock {
        explicit ScopedSharedLock(std::shared_mutex& mtx) : lock(mtx) {}
        void unlock() { lock.unlock(); }
        void close() {lock.lock();}
    private:
        std::shared_lock<std::shared_mutex> lock;
    };

    struct ScopedUniqueLock {
        explicit ScopedUniqueLock(std::shared_mutex& mtx) : lock(mtx) {}
        void unlock() { lock.unlock(); }
        void close() {lock.lock();}
    private:
        std::unique_lock<std::shared_mutex> lock;
    };

#else

struct ScopedSharedLock {
    explicit ScopedSharedLock(std::shared_timed_mutex& mtx) : lock(mtx, std::defer_lock) {
        if (!lock.try_lock_for(std::chrono::seconds(5))) {
            SKSE::log::critical("DEADLOCK DETECTED");
            DebugBreak();
        }
    }
    void unlock() { lock.unlock(); }
    void close() {lock.lock();}
private:
    std::shared_lock<std::shared_timed_mutex> lock;
};

struct ScopedUniqueLock {
    explicit ScopedUniqueLock(std::shared_timed_mutex& mtx) : lock(mtx, std::defer_lock) {
        if (!lock.try_lock_for(std::chrono::seconds(5))) {
            SKSE::log::critical("DEADLOCK DETECTED");
            DebugBreak();
        }
    }
    void unlock() { lock.unlock(); }
    void close() {lock.lock();}
private:
    std::unique_lock<std::shared_timed_mutex> lock;
};

#endif
}

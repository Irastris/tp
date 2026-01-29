#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRFileCache.h"
/* #include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRFileFinder.h"
#include "JSystem/JKernel/JKRHeap.h"

#include <cctype>
#include <string>
#include "global.h" */

JKRFileCache* JKRFileCache::mount(const char* path, JKRHeap* heap, const char* param_3) {
    std::cout << "JKRFileCache::mount() is stubbed" << std::endl;
    return NULL;
}

JKRFileCache::JKRFileCache(const char* path, const char* volume) {
    std::cout << "JKRFileCache::JKRFileCache() is stubbed" << std::endl;
    mParentHeap = NULL;
    mRootPath = NULL;
    mCurrentPath = NULL;
    mVolumePath = NULL;
}

JKRFileCache::~JKRFileCache() {
    std::cout << "JKRFileCache::~JKRFileCache() is stubbed" << std::endl;
}

bool JKRFileCache::becomeCurrent(const char* path) {
    std::cout << "JKRFileCache::becomeCurrent() is stubbed" << std::endl;
    return false;
}

void* JKRFileCache::getResource(const char* path) {
    std::cout << "JKRFileCache::getResource(const char*) is stubbed" << std::endl;
    return NULL;
}

void* JKRFileCache::getResource(u32, const char* path) {
    std::cout << "JKRFileCache::getResource(u32, const char*) is stubbed" << std::endl;
    return NULL;
}

u32 JKRFileCache::readResource(void* dst, u32 dstLength, const char* path) {
    std::cout << "JKRFileCache::readResource(void*, u32, const char*) is stubbed" << std::endl;
    return 0;
}

u32 JKRFileCache::readResource(void* dst, u32 dstLength, u32, const char* path) {
    std::cout << "JKRFileCache::readResource(void*, u32, u32, const char*) is stubbed" << std::endl;
    return 0;
}

void JKRFileCache::removeResourceAll(void) {
    std::cout << "JKRFileCache::removeResourceAll() is stubbed" << std::endl;
}

bool JKRFileCache::removeResource(void* resource) {
    std::cout << "JKRFileCache::removeResource() is stubbed" << std::endl;
    return false;
}

bool JKRFileCache::detachResource(void* resource) {
    std::cout << "JKRFileCache::detachResource() is stubbed" << std::endl;
    return false;
}

u32 JKRFileCache::getResSize(const void* resource) const {
    std::cout << "JKRFileCache::getResSize() is stubbed" << std::endl;
    return 0;
}

u32 JKRFileCache::countFile(const char* path) const {
    std::cout << "JKRFileCache::countFile() is stubbed" << std::endl;
    return 0;
}

JKRFileFinder* JKRFileCache::getFirstFile(const char* path) const {
    std::cout << "JKRFileCache::getFirstFile() is stubbed" << std::endl;
    return NULL;
}

JKRFileCache::CCacheBlock* JKRFileCache::findCacheBlock(const void* resource) const {
    std::cout << "JKRFileCache::findCacheBlock(const void*) is stubbed" << std::endl;
    return NULL;
}

JKRFileCache::CCacheBlock* JKRFileCache::findCacheBlock(u32 fileID) const {
    std::cout << "JKRFileCache::findCacheBlock(u32) is stubbed" << std::endl;
    return NULL;
}

bool JKRFileCache::findFile(char* path, const char* fileName) const {
    std::cout << "JKRFileCache::findFile() is stubbed" << std::endl;
    return false;
}

char* JKRFileCache::getDvdPathName(const char* path) const {
    std::cout << "JKRFileCache::getDvdPathName() is stubbed" << std::endl;
    return NULL;
}

void JKRFileCache::convStrLower(char* buffer) const {
    std::cout << "JKRFileCache::convStrLower() is stubbed" << std::endl;
}

JKRFileCache::CCacheBlock::CCacheBlock(u32 fileId, u32 fileSize, const void* resource)
    : mCacheBlockLink(this) {
    std::cout << "JKRFileCache::CCacheBlock::CCacheBlock() is stubbed" << std::endl;
    mReferenceCount = 0;
    mFileId = 0;
    mFileSize = 0;
    mMemoryPtr = NULL;
}

void* JKRFileCache::getFsResource(const char* path) {
    std::cout << "JKRFileCache::getFsResource() is stubbed" << std::endl;
    return NULL;
}

void* JKRFileCache::getNameResource(u32 type, const char* path) {
    std::cout << "JKRFileCache::getNameResource() is stubbed" << std::endl;
    return NULL;
}

u32 JKRFileCache::readFsResource(void* dst, u32 dstLength, const char* path) {
    std::cout << "JKRFileCache::readFsResource() is stubbed" << std::endl;
    return 0;
}

u32 JKRFileCache::readNameResource(void* dst, u32 dstLength, u32 type, const char* path) {
    std::cout << "JKRFileCache::readNameResource() is stubbed" << std::endl;
    return 0;
}

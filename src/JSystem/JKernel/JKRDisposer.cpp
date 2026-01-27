#include "global.h"
#include "JSystem/JKernel/JKRPlatform.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JKernel/JKRHeap.h"

JKRDisposer::JKRDisposer() : mLink(this) {
    mHeap = JKRHeap::findFromRoot(this);
    if (mHeap) {
        mHeap->appendDisposer(this);
    }
}

JKRDisposer::~JKRDisposer() {
    if (mHeap) {
        mHeap->removeDisposer(this);
    }
}

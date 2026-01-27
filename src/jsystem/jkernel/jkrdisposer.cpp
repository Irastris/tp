#include "global.h"
#include "jsystem/jkernel/jkrplatform.h"
#include "jsystem/jkernel/jkrdisposer.h"
#include "jsystem/jkernel/jkrheap.h"

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

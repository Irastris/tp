#ifndef JKRDISPOSER_H
#define JKRDISPOSER_H

#include "JSystem/JSupport/JSUList.h"

class JKRHeap; // Forward declaration

class JKRDisposer {
public:
    JKRDisposer();
    virtual ~JKRDisposer();

public:
    JKRHeap* mHeap;
    JSULink<JKRDisposer> mLink;
};

#endif

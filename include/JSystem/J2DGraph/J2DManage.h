#ifndef J2DMANAGE_H
#define J2DMANAGE_H

#include <dolphin/types.h>

class JSUInputStream;

struct J2DResReference {
    u16 mCount;
    u16 mOffsets[1];

    char* getResReference(u16) const;
    char* getName(u16) const;
};

struct J2DataManageLink {
    void* mData;
    char* mName;
    J2DataManageLink* mNext;
};

class J2DDataManage {
private:
    J2DataManageLink* mList;

public:
    void* get(char const*);
    void* get(JSUInputStream*);
};

#endif

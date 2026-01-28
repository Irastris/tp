#ifndef JUTRESOURCE_H
#define JUTRESOURCE_H

#include <dolphin/types.h>

class JKRArchive;
class JSUInputStream;

class JUTResReference {
private:
    u8 mType;
    u8 mNameLength;
    char mName[0x100];

public:
    enum ResType {
        RESTYPE_Null = 0,
        RESTYPE_Unk1 = 1,
        RESTYPE_Unk2 = 2,
        RESTYPE_Unk3 = 3,
        RESTYPE_Unk4 = 4,
    };
    JUTResReference() { mType = 0; }
    void* getResource(JSUInputStream*, u32, JKRArchive*);
    void* getResource(void const*, u32, JKRArchive*);
    void* getResource(u32, JKRArchive*);
};

#endif

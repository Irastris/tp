#ifndef JUTCACHEFONT_H
#define JUTCACHEFONT_H

#include "JSystem/JUtility/JUTResFont.h"
#include "global.h"

class JKRAramBlock;

class JUTCacheFont : public JUTResFont {
public:
    struct TGlyphCacheInfo {
        TGlyphCacheInfo* mPrev;
        TGlyphCacheInfo* mNext;
        u16 field_0x8;
        u16 field_0xa;
        u16 field_0xc;
        u16 field_0xe;
        u32 field_0x10;
        u16 mTexFormat;
        u16 field_0x16;
        u16 field_0x18;
        u16 mWidth;
        u16 mHeight;
        u16 field_0x1e;
    };

    struct TCachePage : TGlyphCacheInfo {
        GXTexObj mTexObj;
        u8 mImage[];
    };

    enum EPagingType {
        PAGE_TYPE_0,
        PAGE_TYPE_1,
    };

    JUTCacheFont(ResFONT const*, u32, JKRHeap*);
    void deleteMemBlocks_CacheFont();
    void initialize_state();
    int getMemorySize(ResFONT const*, u16*, u32*, u16*, u32*, u16*, u32*, u32*);
    int initiate(ResFONT const*, void*, u32, JKRHeap*);
    bool internal_initiate(ResFONT const*, void*, u32, JKRHeap*);
    bool allocArea(void*, u32, JKRHeap*);
    bool allocArray(JKRHeap*);
    TGlyphCacheInfo* determineBlankPage();
    void getGlyphFromAram(JUTCacheFont::TGlyphCacheInfo*, JUTCacheFont::TCachePage*, int*, int*);
    TCachePage* loadCache_char_subroutine(int*, bool);
    void invalidiateAllCache();
    void unlink(JUTCacheFont::TGlyphCacheInfo*);
    void prepend(JUTCacheFont::TGlyphCacheInfo*);

    virtual ~JUTCacheFont();
    virtual void loadImage(int, GXTexMapID);
    virtual void setBlock();

    void setPagingType(EPagingType type) { mPagingType = type; }

    static u32 calcCacheSize(u32 param_0, int param_1) { return (ALIGN_NEXT(param_0, 0x20) + 0x40) * param_1; }
    GXTexObj* getTexObj(void* buffer) const { return &((TCachePage*)buffer)->mTexObj; }
    void delete_and_initialize() { deleteMemBlocks_CacheFont(); initialize_state(); }

    u32 getCachePage() const {
        return mCachePage;
    }

    int getMaxSheetSize() const {
        return mMaxSheetSize;
    }

private:
    u32 mTotalWidSize;
    u32 mTotalGlySize;
    u32 mTotalMapSize;
    void* field_0x7c;
    void* field_0x80;
    void* field_0x84;
    u32 mMaxSheetSize;
    EPagingType mPagingType;
    void* mCacheBuffer;
    int field_0x94;
    u32 mCachePage;
    TGlyphCacheInfo* field_0x9c;
    TGlyphCacheInfo* field_0xa0;
    TGlyphCacheInfo* field_0xa4;
    u32 field_0xa8;
    JKRAramBlock* field_0xac;
    u8 field_0xb0;
    int field_0xb4;
};

#endif

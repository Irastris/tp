#ifndef JUTRESFONT_H
#define JUTRESFONT_H

#include "JSystem/JUtility/JUTFont.h"

class JKRHeap;

typedef bool (*IsLeadByte_func)(int);

struct BlockHeader {
    const BlockHeader* getNext() const { return reinterpret_cast<const BlockHeader*>(reinterpret_cast<const u8*>(this) + size); }
    u32 magic;
    u32 size;
};

class JUTResFont : public JUTFont {
public:
    virtual ~JUTResFont();
    virtual void setGX();
    virtual void setGX(JUtility::TColor, JUtility::TColor);
    virtual f32 drawChar_scale(f32, f32, f32, f32, int, bool);
    virtual int getLeading() const;
    virtual s32 getAscent() const;
    virtual s32 getDescent() const;
    virtual s32 getHeight() const;
    virtual s32 getWidth() const;
    virtual void getWidthEntry(int, JUTFont::TWidth*) const;
    virtual s32 getCellWidth() const;
    virtual s32 getCellHeight() const;
    virtual int getFontType() const;
    virtual ResFONT* getResFont() const;
    virtual bool isLeadByte(int) const;
    virtual void loadImage(int, _GXTexMapID);
    virtual void setBlock();

    JUTResFont(ResFONT const*, JKRHeap*);
    JUTResFont();
    void deleteMemBlocks_ResFont();
    void initialize_state();
    bool initiate(ResFONT const*, JKRHeap*);
    bool protected_initiate(ResFONT const*, JKRHeap*);
    void countBlock();
    void loadFont(int, _GXTexMapID, JUTFont::TWidth*);
    int getFontCode(int) const;
    int convertSjis(int, u16*) const;

    inline void delete_and_initialize() {
        deleteMemBlocks_ResFont();
        initialize_state();
    }

    static const int suAboutEncoding_ = 3;
    static IsLeadByte_func const saoAboutEncoding_[suAboutEncoding_];

    int mWidth;
    int mHeight;
    GXTexObj mTexObj;
    int mTexPageIdx;
    const ResFONT* mResFont;
    ResFONT::INF1* mInf1Ptr;
    void** mMemBlocks;
    ResFONT::WID1** mpWidthBlocks;
    ResFONT::GLY1** mpGlyphBlocks;
    ResFONT::MAP1** mpMapBlocks;
    u16 mWid1BlockNum;
    u16 mGly1BlockNum;
    u16 mMap1BlockNum;
    u16 field_0x66;
    u16 mMaxCode;
    const IsLeadByte_func* mIsLeadByte;
};

extern u8 const JUTResFONT_Ascfont_fix12[];
extern u8 const JUTResFONT_Ascfont_fix16[];

#endif

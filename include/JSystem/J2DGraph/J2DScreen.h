#ifndef J2DSCREEN_H
#define J2DSCREEN_H

#include "JSystem/J2DGraph/J2DManage.h"
#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/JUtility/TColor.h"

class J2DMaterial;
class JUTNameTab;

struct J2DScrnHeader {
    u32 mTag;
    u32 mType;
    u32 mFileSize;
    u32 mBlockNum;
    u8 padding[0x10];
};

struct J2DScrnInfoHeader {
    u32 mTag;
    u32 mSize;
    u16 mWidth;
    u16 mHeight;
    u32 mColor;
};

struct J2DScrnBlockHeader {
    u32 mTag;
    s32 mSize;
};

class J2DScreen : public J2DPane {
public:
    virtual ~J2DScreen();
    virtual u16 getTypeID() const;
    virtual void calcMtx();
    virtual void drawSelf(f32, f32, Mtx*);
    virtual J2DPane* search(u64);
    virtual J2DPane* searchUserInfo(u64);
    virtual bool isUsed(ResTIMG const*);
    virtual bool isUsed(ResFONT const*);
    virtual void clearAnmTransform() { J2DPane::clearAnmTransform(); }
    virtual void setAnimation(J2DAnmColor*);
    virtual void setAnimation(J2DAnmTransform* i_bck) { J2DPane::setAnimation(i_bck); }
    virtual void setAnimation(J2DAnmTextureSRTKey*);
    virtual void setAnimation(J2DAnmVtxColor*);
    virtual void setAnimation(J2DAnmTexPattern*);
    virtual void setAnimation(J2DAnmVisibilityFull*);
    virtual void setAnimation(J2DAnmTevRegKey*);
    virtual void setAnimation(J2DAnmBase*);
    virtual void setAnimationVF(J2DAnmVisibilityFull*);
    virtual void setAnimationVC(J2DAnmVtxColor*);
    virtual J2DPane* createPane(J2DScrnBlockHeader const&, JSURandomInputStream*, J2DPane*, u32);
    virtual J2DPane* createPane(J2DScrnBlockHeader const&, JSURandomInputStream*, J2DPane*, u32, JKRArchive*);

    J2DScreen();
    void clean();
    bool setPriority(char const*, u32, JKRArchive*);
    bool setPriority(JSURandomInputStream*, u32, JKRArchive*);
    bool private_set(JSURandomInputStream*, u32, JKRArchive*);
    bool checkSignature(JSURandomInputStream*);
    bool getScreenInformation(JSURandomInputStream*);
    s32 makeHierarchyPanes(J2DPane*, JSURandomInputStream*, u32, JKRArchive*);
    void draw(f32, f32, J2DGrafContext const*);
    J2DResReference* getResReference(JSURandomInputStream*, u32);
    bool createMaterial(JSURandomInputStream*, u32, JKRArchive*);
    static void* getNameResource(char const*);
    void animation();

    void setScissor(bool i_scissor) { mScissor = i_scissor; }

    static J2DDataManage* getDataManage() { return mDataManage; }

    static J2DDataManage* mDataManage;

    bool mScissor;
    u16 mMaterialNum;
    J2DMaterial* mMaterials;
    J2DResReference* mTexRes;
    J2DResReference* mFontRes;
    JUTNameTab* mNameTable;
    JUtility::TColor mColor;
};

#endif

#ifndef J2DPANE_H
#define J2DPANE_H

#include "JSystem/JGeometry.h"
#include "JSystem/JSupport/JSUList.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class J2DAnmBase;
class J2DAnmColor;
class J2DAnmTransform;
class J2DAnmTevRegKey;
class J2DAnmTextureSRTKey;
class J2DAnmVisibilityFull;
class J2DAnmVtxColor;
class J2DGrafContext;
class J2DScreen;
class J2DAnmTexPattern;
class JKRArchive;
class JSURandomInputStream;
struct ResFONT;
struct ResTIMG;

enum J2DRotateAxis {
    ROTATE_X = 'x',
    ROTATE_Y = 'y',
    ROTATE_Z = 'z'
};

enum J2DBasePosition {
    J2DBasePosition_0,
    J2DBasePosition_1,
    J2DBasePosition_2,
    J2DBasePosition_3,
    J2DBasePosition_4,
};

struct J2DPaneHeader {
    u32 mKind;
    u32 mSize;
};

class J2DPane {
public:
    J2DPane();
    J2DPane(J2DPane*, bool, u64, const JGeometry::TBox2<f32>&);
    J2DPane(u64, const JGeometry::TBox2<f32>&);
    J2DPane(J2DPane* other, JSURandomInputStream* stream, u8 arg3);
    void initiate();
    void initialize(J2DPane*, bool, u64, const JGeometry::TBox2<f32>&);
    void initialize(u64 tag, const JGeometry::TBox2<f32>& dim);
    void makePaneStream(J2DPane* other, JSURandomInputStream* stream);
    void changeUseTrans(J2DPane* other);
    bool appendChild(J2DPane* child);
    bool insertChild(J2DPane* before, J2DPane* child);
    void draw(f32 a1, f32 a2, const J2DGrafContext* ctx, bool a4, bool a5);
    void place(const JGeometry::TBox2<f32>& dim);
    JGeometry::TBox2<f32>& getBounds();
    void rotate(f32 offsetX, f32 offsetY, J2DRotateAxis axis, f32 angle);
    void rotate(f32 angle);
    void clip(const JGeometry::TBox2<f32>& bounds);
    void setBasePosition(J2DBasePosition position);
    void setInfluencedAlpha(bool arg1, bool arg2);
    Vec getGlbVtx(u8 arg1) const;
    J2DPane* getFirstChildPane();
    J2DPane* getNextChildPane();
    J2DPane* getParentPane();
    void makePaneExStream(J2DPane* other, JSURandomInputStream* stream);
    void* getPointer(JSURandomInputStream* stream, u32 size, JKRArchive* archive);
    void animationTransform();
    void updateTransform(const J2DAnmTransform* transform);

    virtual ~J2DPane();

    virtual u16 getTypeID() const { return 16; }
    virtual void move(f32 x, f32 y);
    virtual void add(f32 x, f32 y);
    virtual void resize(f32 x, f32 y);
    virtual void setCullBack(bool cull) {
        GXCullMode mode;

        if (cull) {
            mode = GX_CULL_BACK;
        } else {
            mode = GX_CULL_NONE;
        }

        setCullBack(mode);
    }
    virtual void setCullBack(_GXCullMode cmode);
    virtual void setAlpha(u8 alpha) {
        mAlpha = alpha;
    };
    virtual bool setConnectParent(bool connected) {
        mConnected = false;
        return false;
    }
    virtual void calcMtx() {
        if (mPaneTree.getParent() != NULL) {
            makeMatrix(mTranslateX, mTranslateY);
        }
    }
    virtual void update() {}
    virtual void drawSelf(f32 arg1, f32 arg2) {}
    virtual void drawSelf(f32 arg1, f32 arg2, Mtx* mtx) {}
    virtual J2DPane* search(u64 tag);
    virtual J2DPane* searchUserInfo(u64 tag);
    virtual void makeMatrix(f32 a, f32 b) { makeMatrix(a, b, -mBounds.i.x, -mBounds.i.y); }
    virtual void makeMatrix(f32 a, f32 b, f32 c, f32 d);
    virtual bool isUsed(const ResTIMG* timg);
    virtual bool isUsed(const ResFONT* font);
    virtual void clearAnmTransform();
    virtual void rewriteAlpha() {}
    virtual void setAnimation(J2DAnmBase* anm);
    virtual void setAnimation(J2DAnmTransform* anm);
    virtual void setAnimation(J2DAnmColor* anm) {}
    virtual void setAnimation(J2DAnmTexPattern* anm) {}
    virtual void setAnimation(J2DAnmTextureSRTKey* anm) {}
    virtual void setAnimation(J2DAnmTevRegKey* anm) {}
    virtual void setAnimation(J2DAnmVisibilityFull* anm) {}
    virtual void setAnimation(J2DAnmVtxColor* anm) {}
    virtual const J2DAnmTransform* animationTransform(const J2DAnmTransform* transform);
    virtual void setVisibileAnimation(J2DAnmVisibilityFull* visibility);
    virtual void setAnimationVF(J2DAnmVisibilityFull* p_visibility) { setAnimation(p_visibility); }
    virtual void setVtxColorAnimation(J2DAnmVtxColor* vtx_color);
    virtual void setAnimationVC(J2DAnmVtxColor* p_vtxColor) { setAnimation(p_vtxColor); }
    virtual const J2DAnmTransform* animationPane(const J2DAnmTransform* transform);

    f32 getHeight() const { return mBounds.getHeight(); }
    f32 getWidth() const { return mBounds.getWidth(); }
    JSUTree<J2DPane>* getFirstChild() { return mPaneTree.getFirstChild(); }
    JSUTree<J2DPane>* getEndChild() { return mPaneTree.getEndChild(); }
    const JSUTree<J2DPane>* getPaneTree() { return &mPaneTree; }
    u8 getAlpha() const { return mAlpha; }

    f32 getScaleX() const { return mScaleX; }

    f32 getScaleY() const { return mScaleY; }

    f32 getTranslateX() const { return mTranslateX; }

    f32 getTranslateY() const { return mTranslateY; }

    f32 getRotateZ() const { return mRotateZ; }

    f32 getRotOffsetX() const { return mRotateOffsetX; }

    f32 getRotOffsetY() const { return mRotateOffsetY; }

    MtxP getGlbMtx() { return mGlobalMtx; }

    const JGeometry::TBox2<f32>& getGlbBounds() const { return mGlobalBounds; }

    void setMtx(Mtx m) { MTXCopy(m, mPositionMtx); }

    void translate(f32 transX, f32 transY) {
        mTranslateX = transX;
        mTranslateY = transY;
        calcMtx();
    }

    void scale(f32 scaleH, f32 scaleV) {
        mScaleX = scaleH;
        mScaleY = scaleV;
        calcMtx();
    }

    void rotateY(f32 rotate) {
        mRotateY = rotate;
        calcMtx();
    }

    int getKind() const { return mKind; }

    bool isVisible() const { return mVisible; }

    void show() { mVisible = true; }
    void hide() { mVisible = false; }

    bool isInfluencedAlpha() const { return mIsInfluencedAlpha; }
    bool isConnectParent() const { return mConnected; }

    u64 getUserInfo() const { return mUserInfoTag; }
    void setUserInfo(u64 info) { mUserInfoTag = info; }
    const Mtx* getMtx() const { return &mPositionMtx; }

    static s16 J2DCast_F32_to_S16(f32 value, u8 arg2);

    static JGeometry::TBox2<f32> static_mBounds;

public:
    u16 field_0x4;
    int mKind;
    u64 mInfoTag;
    u64 mUserInfoTag;
    JGeometry::TBox2<f32> mBounds;
    JGeometry::TBox2<f32> mGlobalBounds;
    JGeometry::TBox2<f32> mClipRect;
    Mtx mPositionMtx;
    Mtx mGlobalMtx;
    bool mVisible;
    u8 mCullMode;
    u8 mAlpha;
    u8 mColorAlpha;
    bool mIsInfluencedAlpha;
    bool mConnected;
    char mRotAxis;
    u8 mBasePosition;
    f32 mRotateX;
    f32 mRotateY;
    f32 mRotateZ;
    f32 mRotateOffsetX;
    f32 mRotateOffsetY;
    f32 mScaleX;
    f32 mScaleY;
    f32 mTranslateX;
    f32 mTranslateY;
    JSUTree<J2DPane> mPaneTree;
    const J2DAnmTransform* mTransform;
    u32 _fc;
};

#endif

#ifndef J2DTEXTBOX_H
#define J2DTEXTBOX_H

#include "JSystem/J2DGraph/J2DMaterial.h"
#include "JSystem/J2DGraph/J2DPane.h"

class J2DMaterial;
class JUTFont;

enum J2DTextBoxVBinding {
    VBIND_CENTER,
    VBIND_BOTTOM,
    VBIND_TOP
};

enum J2DTextBoxHBinding {
    HBIND_CENTER,
    HBIND_RIGHT,
    HBIND_LEFT
};

struct J2DTbxBlockHeader {
    u32 mTag;
    s32 mSize;
};

struct J2DTextBoxInfo {
    u16 field_0x0;
    u16 field_0x2;
    u16 mMaterialNum;
    s16 mCharSpace;
    s16 mLineSpace;
    u16 mFontSizeX;
    u16 mFontSizeY;
    u8 mHBind;
    u8 mVBind;
    u32 mCharColor;
    u32 mGradColor;
    u8 mConnected;
    char field_0x19[3];
    u16 field_0x1c;
    u16 field_0x1e;
};

class J2DTextBox : public J2DPane {
public:
    struct TFontSize {
        f32 mSizeX;
        f32 mSizeY;
    };

    virtual ~J2DTextBox();
    virtual u16 getTypeID() const;
    virtual void resize(f32, f32);
    virtual bool setConnectParent(bool);
    virtual void drawSelf(f32, f32, Mtx*);
    virtual void drawSelf(f32, f32);
    virtual bool isUsed(ResTIMG const*);
    virtual bool isUsed(ResFONT const*);
    virtual void rewriteAlpha();
    virtual void draw(f32, f32);
    virtual void draw(f32, f32, f32, J2DTextBoxHBinding);
    virtual void setFont(JUTFont*);
    virtual JUTFont* getFont() const { return mFont; }
    virtual bool setBlack(JUtility::TColor);
    virtual bool setWhite(JUtility::TColor white) { mWhiteColor = white; return true; }
    virtual bool setBlackWhite(JUtility::TColor black, JUtility::TColor white) {
        mBlackColor = black;
        mWhiteColor = white;
        return true;
    }
    virtual JUtility::TColor getBlack() const {
        return mBlackColor;
    }
    virtual JUtility::TColor getWhite() const {
        return mWhiteColor;
    }
    virtual J2DMaterial* getMaterial() const { return NULL; }

    J2DTextBox(u64, JGeometry::TBox2<f32> const&, ResFONT const*, char const*, s16, J2DTextBoxHBinding, J2DTextBoxVBinding);
    J2DTextBox(J2DPane*, JSURandomInputStream*, JKRArchive*);
    J2DTextBox(J2DPane*, JSURandomInputStream*, u32, J2DMaterial*);
    J2DTextBox();
    void initiate(ResFONT const*, char const*, s16, J2DTextBoxHBinding, J2DTextBoxVBinding);
    void private_readStream(J2DPane*, JSURandomInputStream*, JKRArchive*);
    char* getStringPtr() const;
    s32 setString(s16, char const*, ...);
    s32 setString(char const*, ...);

    void setFontSize(f32 sizeX, f32 sizeY) {
        f32 x;
        if (sizeX > 0.0f) {
            x = sizeX;
        } else {
            x = 0.0f;
        }
        mFontSizeX = x;

        f32 y;
        if (sizeY > 0.0f) {
            y = sizeY;
        } else {
            y = 0.0f;
        }
        mFontSizeY = y;
    }

    void setFontSize(TFontSize size) { setFontSize(size.mSizeX, size.mSizeY); }
    void getFontSize(TFontSize& size) const {
        size.mSizeX = mFontSizeX;
        size.mSizeY = mFontSizeY;
    }

    void setFontColor(JUtility::TColor i_charColor, JUtility::TColor i_GradientColor) {
        mCharColor = i_charColor;
        mGradientColor = i_GradientColor;
    }

    void setCharColor(JUtility::TColor i_charColor) {
        mCharColor.set(i_charColor);
    }

    void setGradColor(JUtility::TColor i_GradientColor) {
        mGradientColor.set(i_GradientColor);
    }

    void setCharSpace(f32 space) { mCharSpacing = space; }
    f32 getCharSpace() const { return mCharSpacing; }
    void setLineSpace(f32 space) { mLineSpacing = space; }
    f32 getLineSpace() const { return mLineSpacing; }

    J2DTextBoxVBinding getVBinding() const {
        return (J2DTextBoxVBinding)(mFlags & 3);
    }

    J2DTextBoxHBinding getHBinding() const {
        return (J2DTextBoxHBinding)((mFlags >> 2) & 3);
    }

    JUtility::TColor getCharColor() { return mCharColor; }
    JUtility::TColor getGradColor() { return mGradientColor; }
    u16 getStringAllocByte() const { return mStringLength; }

// private:
    JUTFont* mFont;
    JUtility::TColor mCharColor;
    JUtility::TColor mGradientColor;
    f32 field_0x10c;
    f32 field_0x110;
    f32 mCharSpacing;
    f32 mLineSpacing;
    f32 mFontSizeX;
    f32 mFontSizeY;
    char* mStringPtr;
    JUtility::TColor mWhiteColor;
    JUtility::TColor mBlackColor;
    u8 mFlags;
    bool mTextFontOwned;
    u16 mStringLength;
    u8 field_0x134[4];
};

#endif
